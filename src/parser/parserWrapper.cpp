#include "parser/parserWrapper.h"

ParserWrapper::ParserWrapper(Lexer *lexer)
	: m_lexer(lexer), m_rootNodes(std::vector<nodes::CNode*>()) {
}

ParserWrapper::~ParserWrapper() {
	this->clear();
}

Lexer * ParserWrapper::getLexer() const {
	return m_lexer;
}

void ParserWrapper::setRootNode(nodes::CNode * node) {
	m_rootNodes.push_back(node);
}

size_t ParserWrapper::getRootNodesSize() const {
	return m_rootNodes.size();
}

nodes::CNode * ParserWrapper::getRootNodeAt(unsigned int index) {
	if (index < m_rootNodes.size()) {
		return m_rootNodes.at(index);
	}
	return nullptr;
}

void ParserWrapper::clear() {
	for (nodes::CNode * node : m_rootNodes) {
		delete node;
	}
	m_rootNodes.clear();
}