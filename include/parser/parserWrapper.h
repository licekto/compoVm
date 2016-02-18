#pragma once

#include "lexer.h"
#include "compoNode.h"

class ParserWrapper {
private:
                    Lexer                     * m_lexer;
                    std::vector<CCompoNode*>    m_rootNodes;

public:
                                ParserWrapper               (Lexer *lexer);
                                ~ParserWrapper              ();
    Lexer *                     getLexer                    () const;
    int                         parse                       (std::istream& is);
    void                        parseAll                    (std::istream& is);
    void                        error                       (const std::string& message);
    void                        setRootNode                 (CCompoNode * node);
    size_t                      getRootNodesSize            () const;
    CCompoNode *                getRootNodeAt               (unsigned int index);
    void                        clear                       ();
};