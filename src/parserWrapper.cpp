#include "parserWrapper.h"

ParserWrapper::ParserWrapper(Lexer *lexer)
: m_lexer(lexer), m_root(nullptr)
{}

ParserWrapper::~ParserWrapper() {
    delete m_root;
}

Lexer * ParserWrapper::getLexer() const {
    return m_lexer;
}

void ParserWrapper::setRoot(CCompoNode * root) {
    m_root = root;
}

CCompoNode * ParserWrapper::getRoot() {
    return m_root;
}