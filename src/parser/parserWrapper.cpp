#include <memory>

#include "parser/parserWrapper.h"
#include "nodes/compo/serviceSignature.h"

ParserWrapper::ParserWrapper(Lexer *lexer)
	: m_lexer(lexer), m_rootNodes(std::vector<std::shared_ptr<nodes::CNode>>()) {
}

ParserWrapper::~ParserWrapper() {
	this->clearRootNodes();
}

Lexer * ParserWrapper::getLexer() const {
	return m_lexer;
}

void ParserWrapper::setRootNode(std::shared_ptr<nodes::CNode> node) {
	m_rootNodes.push_back(node);
}

size_t ParserWrapper::getRootNodesSize() const {
	return m_rootNodes.size();
}

std::shared_ptr<nodes::CNode> ParserWrapper::getRootNodeAt(unsigned int index) {
	if (index < m_rootNodes.size()) {
		return m_rootNodes.at(index);
	}
	return nullptr;
}

void ParserWrapper::clearRootNodes() {
	for (std::shared_ptr<nodes::CNode> node : m_rootNodes) {
		node.reset();
	}
	m_rootNodes.clear();
}

void ParserWrapper::pushBlock(std::shared_ptr<nodes::procedural::CCompoundBody> block) {
	m_blockStack.push(block);
}

std::shared_ptr<nodes::procedural::CCompoundBody> ParserWrapper::popBlock() {
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

void ParserWrapper::addDescriptorBodyNode(std::shared_ptr<nodes::CNode> node) {
	m_currentDescritporBody.push_back(node);
}

std::vector<std::shared_ptr<nodes::CNode>>* ParserWrapper::getDescriptorBody() {
	return &m_currentDescritporBody;
}

void ParserWrapper::clearDescriptorBody() {
	m_currentDescritporBody.clear();
}

void ParserWrapper::addServiceParam(std::shared_ptr<nodes::procedural::CSymbol> param) {
	m_currentServiceParams.push_back(param);
}

std::vector<std::shared_ptr<nodes::procedural::CSymbol>>* ParserWrapper::getServiceParams() {
	return &m_currentServiceParams;
}

void ParserWrapper::clearServiceParams() {
	m_currentServiceParams.clear();
}

void ParserWrapper::setVisibility(nodes::types::visibilityType type) {
	m_visibilityType = type;
}

nodes::types::visibilityType ParserWrapper::getVisibility() const {
	return m_visibilityType;
}

void ParserWrapper::setAtomicity(bool atomicity) {
	m_atomicity = atomicity;
}

bool ParserWrapper::getAtomicity() const {
	return m_atomicity;
}

void ParserWrapper::addPort(std::shared_ptr<nodes::compo::CPort> port) {
	m_currentPorts.push_back(port);
}

std::vector<std::shared_ptr<nodes::compo::CPort>>* ParserWrapper::getPorts() {
	return &m_currentPorts;
}

void ParserWrapper::clearPorts() {
	m_currentPorts.clear();
}

void ParserWrapper::clearAll() {
	clearDescriptorBody();
	clearServiceParams();
	clearPorts();
}

void ParserWrapper::setCurrentCompoundBody(std::shared_ptr<nodes::procedural::CCompoundBody> body) {
	m_currentCompoundBody = body;
}

std::shared_ptr<nodes::procedural::CCompoundBody> ParserWrapper::getCurrentCompoundBody() {
	return m_currentCompoundBody;
}

void ParserWrapper::addServiceSignature(std::shared_ptr<nodes::compo::CServiceSignature> serviceSignature) {
	m_currentSignaturesList.push_back(serviceSignature);
}

std::vector<std::shared_ptr<nodes::compo::CServiceSignature>>* ParserWrapper::getServiceSignatures() {
	return &m_currentSignaturesList;
}

void ParserWrapper::clearServiceSignatures() {
	m_currentSignaturesList.clear();
}
