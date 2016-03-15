#include <memory>

#include "parser/parserWrapper.h"
#include "ast/compo/architecture.h"
#include "ast/compo/provision.h"
#include "ast/program.h"

ParserWrapper::ParserWrapper(Lexer *lexer)
	: m_lexer(lexer), m_root(std::make_shared<ast::CProgram>()) {
	pushServiceParams();
}

ParserWrapper::~ParserWrapper() {
	this->clearRootNodes();
}

Lexer * ParserWrapper::getLexer() const {
	return m_lexer;
}

void ParserWrapper::addRootNode(std::shared_ptr<ast::CNode> node) {
	m_root->addNode(node);
}

std::shared_ptr<ast::CProgram> ParserWrapper::getRootNode() {
    return m_root;
}

void ParserWrapper::clearRootNodes() {
	m_root.reset();
        m_root = std::make_shared<ast::CProgram>();
}

void ParserWrapper::pushBlock(std::shared_ptr<ast::procedural::CCompoundBody> block) {
	m_blockStack.push(block);
}

std::shared_ptr<ast::procedural::CCompoundBody> ParserWrapper::popBlock() {
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

void ParserWrapper::setInProvision(std::shared_ptr<ast::compo::CProvision> inProv) {
	m_currentInteralProvision = inProv;
}

std::shared_ptr<ast::compo::CProvision> ParserWrapper::getInProvision() {
	return m_currentInteralProvision;
}

void ParserWrapper::setExProvision(std::shared_ptr<ast::compo::CProvision> exProv) {
	m_currentExteralProvision = exProv;
}

std::shared_ptr<ast::compo::CProvision> ParserWrapper::getExProvision() {
	return m_currentExteralProvision;
}

void ParserWrapper::setInRequirement(std::shared_ptr<ast::compo::CRequirement> inReq) {
	m_currentInteralRequirement = inReq;
}

std::shared_ptr<ast::compo::CRequirement> ParserWrapper::getInRequirement() {
	return m_currentInteralRequirement;
}

void ParserWrapper::setExRequirement(std::shared_ptr<ast::compo::CRequirement> exReq) {
	m_currentExteralRequirement = exReq;
}

std::shared_ptr<ast::compo::CRequirement> ParserWrapper::getExRequirement() {
	return m_currentExteralRequirement;
}

void ParserWrapper::setArchitecture(std::shared_ptr<ast::compo::CArchitecture> arch) {
	m_architecture = arch;
}

std::shared_ptr<ast::compo::CArchitecture> ParserWrapper::getArchitecture() {
	return m_architecture;
}

void ParserWrapper::addDescriptorService(std::shared_ptr<ast::compo::CService> service) {
	m_currentDescritporServices.push_back(service);
}

std::vector<std::shared_ptr<ast::compo::CService>>* ParserWrapper::getDescriptorServices() {
	return &m_currentDescritporServices;
}

void ParserWrapper::clearDescriptorServices() {
	m_currentDescritporServices.clear();
}

void ParserWrapper::addDescriptorConstraint(std::shared_ptr<ast::compo::CConstraint> constraint) {
	m_currentDescritporConstraints.push_back(constraint);
}

std::vector<std::shared_ptr<ast::compo::CConstraint>>* ParserWrapper::getDescriptorConstraints() {
	return &m_currentDescritporConstraints;
}

void ParserWrapper::clearDescriptorConstraints() {
	m_currentDescritporConstraints.clear();
}

void ParserWrapper::addServiceParam(std::shared_ptr<ast::CNode> param) {
	//m_currentServiceParams.push_back(param);
	if (m_currentServiceParamsStack.empty()) {
		pushServiceParams();
	}
	m_currentServiceParamsStack.top().push_back(param);
}

std::vector<std::shared_ptr<ast::CNode>>* ParserWrapper::getServiceParams() {
	//return &m_currentServiceParams;
	if (m_currentServiceParamsStack.empty()) {
		pushServiceParams();
	}
	return &m_currentServiceParamsStack.top();
}

void ParserWrapper::pushServiceParams() {
	m_currentServiceParamsStack.push(std::vector<std::shared_ptr<ast::CNode>>(0));
}

void ParserWrapper::popServiceParams() {
	m_currentServiceParamsStack.pop();
}

void ParserWrapper::setVisibility(ast::types::visibilityType type) {
	m_visibilityType = type;
}

ast::types::visibilityType ParserWrapper::getVisibility() const {
	return m_visibilityType;
}

void ParserWrapper::setAtomicity(bool atomicity) {
	m_atomicity = atomicity;
}

bool ParserWrapper::getAtomicity() const {
	return m_atomicity;
}

void ParserWrapper::addPort(std::shared_ptr<ast::compo::CPort> port) {
	m_currentPorts.push_back(port);
}

std::vector<std::shared_ptr<ast::compo::CPort>>* ParserWrapper::getPorts() {
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

void ParserWrapper::setCurrentCompoundBody(std::shared_ptr<ast::procedural::CCompoundBody> body) {
	m_currentCompoundBody = body;
}

std::shared_ptr<ast::procedural::CCompoundBody> ParserWrapper::getCurrentCompoundBody() {
	return m_currentCompoundBody;
}

void ParserWrapper::addServiceSignature(std::shared_ptr<ast::compo::CServiceSignature> serviceSignature) {
	m_currentSignaturesList.push_back(serviceSignature);
}

std::vector<std::shared_ptr<ast::compo::CServiceSignature>>* ParserWrapper::getServiceSignatures() {
	return &m_currentSignaturesList;
}

void ParserWrapper::clearServiceSignatures() {
	m_currentSignaturesList.clear();
}

void ParserWrapper::setPortName(std::shared_ptr<ast::procedural::CSymbol> name) {
	m_currentPortName = name;
}

std::shared_ptr<ast::procedural::CSymbol> ParserWrapper::getPortName() const {
	return m_currentPortName;
}

void ParserWrapper::setCollectivity(bool collectivity) {
	m_collectivity = collectivity;
}

bool ParserWrapper::getCollectivity() const {
	return m_collectivity;
}

void ParserWrapper::addArchitectureNode(std::shared_ptr<ast::compo::CBind> bindNode) {
	m_currentArchitectureBody.push_back(bindNode);
}

std::vector<std::shared_ptr<ast::compo::CBind>> * ParserWrapper::getArchitectureBody() {
	return &m_currentArchitectureBody;
}

void ParserWrapper::clearArchitectureBody() {
	m_currentArchitectureBody.clear();
}
