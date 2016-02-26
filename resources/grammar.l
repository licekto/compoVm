%state COMMENT
%state STRING

%option c++
%option yyclass="Lexer"
%option noyywrap

%{
#include <iostream>
#include <cstdlib>
#include "parser/parserWrapper.h"
#include "generated/parser.h"
#include "nodes/compoNode.h"
#include "nodes/proceduralNodes/compoSymbol.h"
#include "nodes/proceduralNodes/compoConstant.h"
#include "nodes/proceduralNodes/compoStringLiteral.h"

std::string buffer;
%}

Letter                      [a-zA-Z]
DecimalDigit                [0-9]
IntegerLiteral              ([+-]?{DecimalDigit}+)
LetterOrDigit               ({Letter}|{DecimalDigit})
Whitespace                  [\n\r\t ]
Identifier                  ({Letter}|[_]){LetterOrDigit}*

%%

<INITIAL>{Whitespace}+                  {}

<INITIAL>\"                             {BEGIN(COMMENT);}

<INITIAL>\'                             {BEGIN(STRING);}

<COMMENT>\"                             {BEGIN(INITIAL);}

    /* Multi-line comments allowed */
<COMMENT>\n                             {}
<COMMENT>.                              {}

<STRING>[^\\']                          {buffer.append(yytext);}

<STRING>\\.?                            {buffer.append(yytext+1);} // skip backslash

<STRING>\'                              {
                                            yylval = new compo::CCompoStringLiteral(buffer);
                                            BEGIN(INITIAL);
                                            return STRING_LITERAL;
                                        }

<INITIAL>descriptor                     {return DESCRIPTOR;}

<INITIAL>interface                      {return INTERFACE;}

<INITIAL>extends                        {return EXTENDS;}

<INITIAL>architecture                   {return ARCHITECTURE;}

<INITIAL>constraint                     {return CONSTRAINT;}

<INITIAL>service                        {return SERVICE;}

<INITIAL>internally                     {return INTERNALLY;}

<INITIAL>externally                     {return EXTERNALLY;}

<INITIAL>provides                       {return PROVIDES;}

<INITIAL>requires                       {return REQUIRES;}

<INITIAL>atomic                         {return ATOMIC;}

<INITIAL>connect                        {return CONNECT;}

<INITIAL>disconnect                     {return DISCONNECT;}

<INITIAL>delegate			{return DELEGATE;}

<INITIAL>return				{return RETURN;}

<INITIAL>to				{return TO;}

<INITIAL>inject-with                    {return INJECTWITH;}

<INITIAL>of-kind                        {return OFKIND;}

<INITIAL>for				{return FOR;}

<INITIAL>if				{return IF;}

<INITIAL>else				{return ELSE;}

<INITIAL>while				{return WHILE;}

<INITIAL>":="				{return ASSIGNMENT;}

<INITIAL>"*"				{return '*';}

<INITIAL>"@"				{return '@';}

<INITIAL>"#"				{return '#';}

<INITIAL>"."				{return '.';}

<INITIAL>","				{return ',';}

<INITIAL>":"                            {return ':';}

<INITIAL>";"                            {return ';';}

<INITIAL>"&"                            {return '&';}

<INITIAL>"|"                            {return '|';}

<INITIAL>"'"                            {return '\'';}

<INITIAL>"+"                            {return '+';}

<INITIAL>"-"                            {return '-';}

<INITIAL>"/"                            {return '/';}

<INITIAL>"<"                            {return '<';}

<INITIAL>">"                            {return '>';}

<INITIAL>"("                            {return '(';}

<INITIAL>")"                            {return ')';}

<INITIAL>"["                            {return '[';}

<INITIAL>"]"                            {return ']';}

<INITIAL>"{"                            {return '{';}

<INITIAL>"}"                            {return '}';}

<INITIAL>{Identifier}                   {
                                            yylval = new compo::CCompoSymbol(std::string(yytext, yyleng));
                                            return IDENTIFIER;
                                        }

<INITIAL>{IntegerLiteral}               {
                                            yylval = new compo::CCompoConstant(atoll(yytext));
                                            return CONSTANT;
                                        }

<<EOF>>                                 {return END;}

<INITIAL>.                              {std::cerr << "Syntax error!" << std::endl; return END;}

%%

Lexer::Lexer() : yyFlexLexer()
{

}

void Lexer::resetState()
{
    yy_start = 1;
}
