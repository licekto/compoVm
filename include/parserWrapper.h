#pragma once

#include "lexer.h"
#include "compoNode.h"

class ParserWrapper {
private:
    Lexer       * m_lexer;
    CCompoNode  * m_root;

public:
                    ParserWrapper   (Lexer *lexer) : m_lexer(lexer), m_root(nullptr) {};
    Lexer *         getLexer        () const {return m_lexer;}
    int             parse           (std::istream& is);
    void            error           (const std::string& message);
    void            setRoot         (CCompoNode * root) {m_root = root;}
    CCompoNode *    getRoot         () {return m_root;}
};