%state COMMENT

%option c++
%option yyclass="Lexer"
%option noyywrap

%{
#include <iostream>
#include "parserWrapper.h"
#include "parser.h"
#include "compoNode.h"
%}

Letter                      [a-zA-Z]
DecimalDigit                [0-9]
LetterOrDigit               ({Letter}|{DecimalDigit})
Whitespace                  [\n\r\t ]
Identifier                  ({Letter}|[_]){LetterOrDigit}*

%%

<INITIAL>{Whitespace}+                  {}

<INITIAL>\"                             {BEGIN(COMMENT);}

<COMMENT>\"                             {BEGIN(INITIAL);}

    /* Multi-line comments allowed? */
<COMMENT>\n                             {}
<COMMENT>.                              {}

<INITIAL>Descriptor                     {return TOKEN_DESCRIPTOR;}

<INITIAL>extends                        {
                                            return TOKEN_EXTENDS;
                                        }

<INITIAL>{Identifier}                   {
                                            yylval = new CCompoSymbol(std::string(yytext, yyleng));
                                            return TOKEN_IDENTIFIER;
                                        }

<<EOF>>                                 {return TOKEN_END;}

<INITIAL>.                              {std::cerr << "Syntax error!" << std::endl; return TOKEN_END;}

%%

Lexer::Lexer() : yyFlexLexer()
{

}

void Lexer::resetState()
{
    yy_start = 1;
}