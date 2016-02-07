%{
#include <iostream>
#include "parserWrapper.h"
#include "lexer.h"
#include "compoNode.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)

NODE_VECTOR currentBody;

SYMBOL_VECTOR currentServiceParams;
NODE_VECTOR currentServiceBody;
CCompoService * currentService = nullptr;
CCompoNode *root = nullptr;

%}

%define api.value.type {CCompoNode*}
%define parse.error verbose
%define parse.lac full

%debug

%parse-param {ParserWrapper* parser}

%start S

%token TOKEN_DESCRIPTOR
%token TOKEN_EXTENDS
%token TOKEN_ARCHITECTURE
%token TOKEN_CONSTRAINT
%token TOKEN_SERVICE
%token TOKEN_INTERNALLY
%token TOKEN_EXTERNALLY
%token TOKEN_PROVIDES
%token TOKEN_REQUIRES
%token TOKEN_ATOMIC
%token TOKEN_CONNECT
%token TOKEN_DISCONNECT
%token TOKEN_OPENBRACE
%token TOKEN_CLOSEBRACE
%token TOKEN_OPENPAR
%token TOKEN_CLOSEPAR
%token TOKEN_IDENTIFIER
%token TOKEN_END        0   "end of file"

%%

S               :   descriptors TOKEN_END
                    {
                        parser->setRoot(root); YYACCEPT; return 0;
                    }

descriptors     :   descriptor descriptors
                |   /* epsilon */
                ;

descriptor      :   TOKEN_DESCRIPTOR TOKEN_IDENTIFIER inheritance TOKEN_OPENBRACE compoExprs TOKEN_CLOSEBRACE
                    {
                        CCompoDescriptor *descriptor = new CCompoDescriptor((CCompoSymbol*) $2, nullptr, currentBody);
                        if ($3) {
                            descriptor->setExtends((CCompoSymbol*) $3);
                        }
                        root = descriptor;
                    }

inheritance     :   TOKEN_EXTENDS TOKEN_IDENTIFIER
                    {
                        $$ = $2;
                    }
                |   /* epsilon */
                    {$$ = nullptr;}
                ;

compoExprs      :   compoExpr compoExprs
                    {
                        currentBody.push_back($1);
                        currentService = nullptr;
                    }
                |   /* epsilon */
                ;

compoExpr       :   services
                    {
                        $$ = currentService;
                    }
                |   exRequirements
                |   exProvisions
                ;

exProvisions    :   externally TOKEN_PROVIDES TOKEN_IDENTIFIER TOKEN_OPENBRACE TOKEN_CLOSEBRACE
                ;

exRequirements  :   externally TOKEN_REQUIRES TOKEN_IDENTIFIER TOKEN_OPENBRACE TOKEN_CLOSEBRACE
                ;

externally      :   TOKEN_EXTERNALLY
                |   /* epsilon */
                ;

services        :   TOKEN_SERVICE serviceSign
                ;

serviceSign     :   TOKEN_IDENTIFIER TOKEN_OPENPAR serviceParams TOKEN_CLOSEPAR TOKEN_OPENBRACE TOKEN_CLOSEBRACE
                    {
                        currentService = new CCompoService((CCompoSymbol*) $1, currentServiceParams, currentServiceBody);
                        currentServiceParams.clear();
                    }
                ;

serviceParams   :   TOKEN_IDENTIFIER
                    {
                        currentServiceParams.push_back((CCompoSymbol*) $1);
                    }
                |   TOKEN_IDENTIFIER "," serviceParams
                    {
                        currentServiceParams.push_back((CCompoSymbol*) $1);
                    }
                |   /* epsilon */
                ;

%%

void ParserWrapper::error(const std::string& message) {
    std::cerr << message << std::endl;
}

int ParserWrapper::parse(std::istream& is) {

    m_lexer->switch_streams(&is, &std::cout);
    m_lexer->resetState();

    return yyparse(this);
}