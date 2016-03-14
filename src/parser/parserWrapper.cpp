#include <memory>

#include "parser/parserWrapper.h"

ParserWrapper::ParserWrapper(Lexer *lexer)
	: m_lexer(lexer), m_rootNodes(std::vector<std::shared_ptr<ast::CNode>>()) {
	pushServiceParams();
}

ParserWrapper::~ParserWrapper() {
	this->clearRootNodes();
}

Lexer * ParserWrapper::getLexer() const {
	return m_lexer;
}

void ParserWrapper::addRootNode(std::shared_ptr<ast::CNode> node) {
	m_rootNodes.push_back(node);
}

size_t ParserWrapper::getRootNodesSize() const {
	return m_rootNodes.size();
}

std::shared_ptr<ast::CNode> ParserWrapper::getRootNodeAt(unsigned int index) {
	if (index < m_rootNodes.size()) {
		return m_rootNodes.at(index);
	}
	return nullptr;
}

void ParserWrapper::clearRootNodes() {
	for (std::shared_ptr<ast::CNode> node : m_rootNodes) {
		node.reset();
	}
	m_rootNodes.clear();
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

void ParserWrapper::addDescriptorBodyNode(std::shared_ptr<ast::CNode> node) {
	m_currentDescritporBody.push_back(node);
}

std::vector<std::shared_ptr<ast::CNode>>* ParserWrapper::getDescriptorBody() {
	return &m_currentDescritporBody;
}

void ParserWrapper::clearDescriptorBody() {
	m_currentDescritporBody.clear();
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
	clearDescriptorBody();
	clearPorts();
	clearArchitectureBody();
	clearServiceSignatures();
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
