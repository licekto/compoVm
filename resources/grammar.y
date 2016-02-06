%{
#include <iostream>
#include "parserWrapper.h"
#include "lexer.h"
#include "compoNode.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)
%}

%define api.value.type {CCompoNode*}
%define parse.error verbose
%define parse.lac full

%debug

%parse-param {ParserWrapper* parser}

%start S

%token TOKEN_IDENTIFIER
%token TOKEN_DESCRIPTOR
%token TOKEN_EXTENDS
%token TOKEN_END        0   "end of file"

%%

S               :   descriptors TOKEN_END {parser->setRoot($1); YYACCEPT; return 0;}

descriptors     :   descriptor descriptors  {$$ = $1;}
                |
                ;

descriptor      :   TOKEN_DESCRIPTOR TOKEN_IDENTIFIER inheritance
                    {
                        CCompoDescriptor *descriptor = new CCompoDescriptor((CCompoSymbol*) $2, nullptr, nullptr);
                        if ($3) {
                            descriptor->setExtends((CCompoSymbol*) $3);
                        }
                        $$ = descriptor;
                    }

inheritance     :   TOKEN_EXTENDS TOKEN_IDENTIFIER
                    {
                        $$ = $2;
                    }
                |   {$$ = nullptr;}
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