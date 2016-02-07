#pragma once

#include "lexer.h"
#include "compoNode.h"

class ParserWrapper {
private:
                    Lexer       * m_lexer;
                    CCompoNode  * m_root;

public:
                    ParserWrapper   (Lexer *lexer);
                    ~ParserWrapper  ();
    Lexer *         getLexer        () const;
    int             parse           (std::istream& is);
    void            error           (const std::string& message);
    void            setRoot         (CCompoNode * root);
    CCompoNode *    getRoot         ();
};