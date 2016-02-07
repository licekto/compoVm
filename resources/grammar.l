%state COMMENT

%option c++
%option yyclass="Lexer"
%option noyywrap

%{
#include <iostream>
#include "parserWrapper.h"
#include "parser.h"
#include "compoNode.h"
#include "compoSymbol.h"
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

<INITIAL>extends                        {return TOKEN_EXTENDS;}

<INITIAL>architecture                   {return TOKEN_ARCHITECTURE;}

<INITIAL>constraint                     {return TOKEN_CONSTRAINT;}

<INITIAL>service                        {return TOKEN_SERVICE;}

<INITIAL>internally                     {return TOKEN_INTERNALLY;}

<INITIAL>externally                     {return TOKEN_EXTERNALLY;}

<INITIAL>provides                       {return TOKEN_PROVIDES;}

<INITIAL>requires                       {return TOKEN_REQUIRES;}

<INITIAL>atomic                         {return TOKEN_ATOMIC;}

<INITIAL>connect                        {return TOKEN_CONNECT;}

<INITIAL>disconnect                     {return TOKEN_DISCONNECT;}

<INITIAL>delegate			{return TOKEN_DELEGATE;}

<INITIAL>return				{return TOKEN_RETURN;}

<INITIAL>to				{return TOKEN_TO;}

<INITIAL>"@"				{return TOKEN_AT;}

<INITIAL>":="				{return TOKEN_ASSIGN;}

<INITIAL>"."				{return TOKEN_DOT;}

<INITIAL>","				{return TOKEN_COMMA;}

<INITIAL>"{"                            {return TOKEN_OPENBRACE;}

<INITIAL>"}"                            {return TOKEN_CLOSEBRACE;}

<INITIAL>"("                            {return TOKEN_OPENPAR;}

<INITIAL>")"                            {return TOKEN_CLOSEPAR;}

<INITIAL>":"                            {return TOKEN_COLON;}

<INITIAL>";"                            {return TOKEN_SEMICOLON;}

<INITIAL>"|"                            {return TOKEN_PIPE;}

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