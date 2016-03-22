#include <memory>

#include "parser/parserWrapper.h"

ParserWrapper::ParserWrapper(ptr(Lexer) lexer, ptr(ast::semantic::CGlobalDescriptorTable) descriptorTable)
	: m_lexer(lexer), m_descriptorTable(descriptorTable), m_root(new_ptr(ast_program)()) {
	pushServiceParams();
}

ParserWrapper::~ParserWrapper() {
	this->clearRootNodes();
}

ptr(Lexer) ParserWrapper::getLexer() const {
	return m_lexer;
}

void ParserWrapper::addSymbolToDescriptorTable(ptr(ast_descriptorinterface) node) {
    if (m_descriptorTable.use_count()) {
        if (m_descriptorTable->symbolFound(node->getNameSymbol()->getStringValue())) {
            throw exceptions::semantic::CRedefinitionDescriptorException(node->getNameSymbol()->getStringValue());
        }
        m_descriptorTable->addSymbol(node);
    }
}

ptr(ast::semantic::CGlobalDescriptorTable) ParserWrapper::getDescriptorTable() {
    return m_descriptorTable;
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

void ParserWrapper::setInProvision(ptr(ast_provision) inProv) {
	m_currentInteralProvision = inProv;
}

ptr(ast_provision) ParserWrapper::getInProvision() {
	return m_currentInteralProvision;
}

void ParserWrapper::setExProvision(ptr(ast_provision) exProv) {
	m_currentExteralProvision = exProv;
}

ptr(ast_provision) ParserWrapper::getExProvision() {
	return m_currentExteralProvision;
}

void ParserWrapper::setInRequirement(ptr(ast_requirement) inReq) {
	m_currentInteralRequirement = inReq;
}

ptr(ast_requirement) ParserWrapper::getInRequirement() {
	return m_currentInteralRequirement;
}

void ParserWrapper::setExRequirement(ptr(ast_requirement) exReq) {
	m_currentExteralRequirement = exReq;
}

ptr(ast_requirement) ParserWrapper::getExRequirement() {
	return m_currentExteralRequirement;
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

void ParserWrapper::setVisibility(ast::nodes::types::visibilityType type) {
	m_visibilityType = type;
}

ast::nodes::types::visibilityType ParserWrapper::getVisibility() const {
	return m_visibilityType;
}

void ParserWrapper::setAtomicity(bool atomicity) {
	m_atomicity = atomicity;
}

bool ParserWrapper::getAtomicity() const {
	return m_atomicity;
}

void ParserWrapper::addPort(ptr(ast_port) port) {
	m_currentPorts.push_back(port);
}

std::vector<ptr(ast_port)>* ParserWrapper::getPorts() {
	return &m_currentPorts;
}

void ParserWrapper::clearPorts() {
	m_currentPorts.clear();
}

void ParserWrapper::clearAll() {
	clearPorts();
	clearArchitectureBody();
	clearServiceSignatures();
	clearDescriptorServices();
	clearDescriptorConstraints();
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
