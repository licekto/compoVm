#include <memory>

#include "parser/parserWrapper.h"
#include "exceptions/semantic/redefinedPortException.h"

ParserWrapper::ParserWrapper(ptr(Lexer) lexer, ptr(ast::semantic::CSyntaxDescriptorTable) descriptorTable)
	: m_lexer(lexer), m_descriptorTable(descriptorTable), m_root(new_ptr(ast_program)()) {
	pushServiceParams();
}

ParserWrapper::~ParserWrapper() {
	this->clearRootNodes();
}

int ParserWrapper::parse(const std::string& code) {
	std::stringstream input;
	input.str(code);

	return parse(input);
}

ptr(Lexer) ParserWrapper::getLexer() const {
	return m_lexer;
}

void ParserWrapper::addSymbolToDescriptorTable(ptr(ast_descriptorinterface) node) {
	if (m_descriptorTable.use_count()) {
		if (m_descriptorTable->symbolFound(node->getNameSymbol()->getStringValue())) {
			if (node->getNodeType() == type_node::DESCRIPTOR) {
				throw exceptions::semantic::CRedefinedDescriptorException(node->getNameSymbol()->getStringValue());
			} else if (node->getNodeType() == type_node::INTERFACE) {
				throw exceptions::semantic::CRedefinedInterfaceException(node->getNameSymbol()->getStringValue());
			}

		}
		m_descriptorTable->addSymbol(node);
	}
}

ptr(ast::semantic::CSyntaxDescriptorTable) ParserWrapper::getDescriptorTable() {
	return m_descriptorTable;
}

void ParserWrapper::clearDescriptorTable() {
	if (m_descriptorTable.use_count()) {
		m_descriptorTable->clear();
	}
}

void ParserWrapper::addRootNode(ptr(ast_node) node) {
	m_root->addNode(node);
}

ptr(ast_program) ParserWrapper::getRootNode() {
	return m_root;
}

void ParserWrapper::clearRootNodes() {
	m_root.reset();
	m_root = new_ptr(ast_program)();
}

void ParserWrapper::pushBlock(ptr(ast_compound) block) {
	m_blockStack.push(block);
}

ptr(ast_compound) ParserWrapper::popBlock() {
	if (m_blockStack.empty()) {
		return nullptr;
	}
	auto blockPtr = m_blockStack.top();
	m_blockStack.pop();
	return blockPtr;
}

bool ParserWrapper::isStackEmpty() const {
	return m_blockStack.empty();
}

void ParserWrapper::setArchitecture(ptr(ast_architecture) arch) {
	m_architecture = arch;
}

ptr(ast_architecture) ParserWrapper::getArchitecture() {
	return m_architecture;
}

void ParserWrapper::addDescriptorService(ptr(ast_service) service) {
	m_currentDescritporServices.push_back(service);
}

std::vector<ptr(ast_service)>* ParserWrapper::getDescriptorServices() {
	return &m_currentDescritporServices;
}

void ParserWrapper::clearDescriptorServices() {
	m_currentDescritporServices.clear();
}

void ParserWrapper::addDescriptorConstraint(ptr(ast_constraint) constraint) {
	m_currentDescritporConstraints.push_back(constraint);
}

std::vector<ptr(ast_constraint)>* ParserWrapper::getDescriptorConstraints() {
	return &m_currentDescritporConstraints;
}

void ParserWrapper::clearDescriptorConstraints() {
	m_currentDescritporConstraints.clear();
}

void ParserWrapper::addServiceParam(ptr(ast_node) param) {
	if (m_currentServiceParamsStack.empty()) {
		pushServiceParams();
	}
	m_currentServiceParamsStack.top().push_back(param);
}

std::vector<ptr(ast_node)>* ParserWrapper::getServiceParams() {
	if (m_currentServiceParamsStack.empty()) {
		pushServiceParams();
	}
	return &m_currentServiceParamsStack.top();
}

void ParserWrapper::pushServiceParams() {
	m_currentServiceParamsStack.push(std::vector<ptr(ast_node)>(0));
}

void ParserWrapper::popServiceParams() {
	m_currentServiceParamsStack.pop();
}

void ParserWrapper::setVisibility(types::visibilityType type) {
	m_visibilityType = type;
}

types::visibilityType ParserWrapper::getVisibility() const {
	return m_visibilityType;
}

void ParserWrapper::setAtomicity(bool atomicity) {
	m_atomicity = atomicity;
}

bool ParserWrapper::getAtomicity() const {
	return m_atomicity;
}

void ParserWrapper::addPort(ptr(ast_port) port) {
	auto it = std::find_if(m_currentPorts.begin(), m_currentPorts.end(), [port] (ptr(ast_port) definedPort) {
		return definedPort->getNameSymbol()->getStringValue() == port->getNameSymbol()->getStringValue();
	});

	if (it != m_currentPorts.end()) {
		throw exceptions::semantic::CRedefinedPortException(port->getNameSymbol()->getStringValue());
	}
	m_currentPorts.push_back(port);
}

std::vector<ptr(ast_port)>* ParserWrapper::getPorts() {
	return &m_currentPorts;
}

void ParserWrapper::clearPorts() {
	m_currentPorts.clear();
}

void ParserWrapper::clearContext() {
	clearPorts();
	clearArchitectureBody();
	clearServiceSignatures();
	clearDescriptorServices();
	clearDescriptorConstraints();
	clearRefs();
}

void ParserWrapper::clearRefs() {
	m_architecture = nullptr;
	m_currentCompoundBody = nullptr;
	m_currentPortName = nullptr;
	m_serviceBody = nullptr;
}

void ParserWrapper::clearAll() {
	clearContext();
	clearDescriptorTable();
	clearPorts();
	clearRootNodes();
	clearRefs();
}

void ParserWrapper::setCurrentCompoundBody(ptr(ast_compound) body) {
	m_currentCompoundBody = body;
}

ptr(ast_compound) ParserWrapper::getCurrentCompoundBody() {
	return m_currentCompoundBody;
}

void ParserWrapper::addServiceSignature(ptr(ast_servicesignature) serviceSignature) {
	m_currentSignaturesList.push_back(serviceSignature);
}

std::vector<ptr(ast_servicesignature)>* ParserWrapper::getServiceSignatures() {
	return &m_currentSignaturesList;
}

void ParserWrapper::clearServiceSignatures() {
	m_currentSignaturesList.clear();
}

void ParserWrapper::setPortName(ptr(ast_symbol) name) {
	m_currentPortName = name;
}

ptr(ast_symbol) ParserWrapper::getPortName() const {
	return m_currentPortName;
}

void ParserWrapper::setCollectivity(bool collectivity) {
	m_collectivity = collectivity;
}

bool ParserWrapper::getCollectivity() const {
	return m_collectivity;
}

void ParserWrapper::addArchitectureNode(ptr(ast_bind) bindNode) {
	m_currentArchitectureBody.push_back(bindNode);
}

std::vector<ptr(ast_bind)> * ParserWrapper::getArchitectureBody() {
	return &m_currentArchitectureBody;
}

void ParserWrapper::clearArchitectureBody() {
	m_currentArchitectureBody.clear();
}

void ParserWrapper::addServiceBody(std::shared_ptr<ast_compound> body) {
	m_serviceBody = body;
}

std::shared_ptr<ast_compound> ParserWrapper::getServiceBody() const {
	return m_serviceBody;
}

void ParserWrapper::parseServices() {
	for (size_t i = 0; i < m_root->getNodesSize(); ++i) {
		if (m_root->getNodeAt(i)->getNodeType() == type_node::DESCRIPTOR) {
			ptr(ast_descriptor) descriptor = cast(ast_descriptor)(m_root->getNodeAt(i));
			for (size_t j = 0; j < descriptor->getServicesSize(); ++j) {
				ptr(ast_service) service = descriptor->getServiceAt(j);

				std::stringstream input;
				std::string serviceCode = service->getBodyCode();
				input.str(serviceCode);

				m_serviceBody.reset();

				parse(input);

				service->setParsedBodyNode(m_serviceBody);
			}
		}
	}
}

void ParserWrapper::setRole(types::roleType role) {
	m_role = role;
}

types::roleType ParserWrapper::getRole() const {
	return m_role;
}
