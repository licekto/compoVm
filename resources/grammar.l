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

#include "definitions.h"

std::string buffer;
%}

IntegerLiteral              ([+-]?[0-9]+)
Whitespace                  [\n\r\t ]
Identifier                  [a-zA-Z][a-zA-Z_0-9]*

%%

<INITIAL>{Whitespace}+                  {}

<INITIAL>"/*"                           {BEGIN(COMMENT);}

<INITIAL>\"                             {BEGIN(STRING);}

<COMMENT>"*/"                           {BEGIN(INITIAL);}

    /* Multi-line comments allowed */
<COMMENT>\n                             {}
<COMMENT>.                              {}

<STRING>[^\\"]                          {buffer.append(yytext);}

<STRING>\\.?                            {buffer.append(yytext+1);} // skip backslash

<STRING>\"                              {
                                            yylval = new_ptr(ast_string)(buffer);
                                            BEGIN(INITIAL);
                                            buffer.clear();
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

<INITIAL>from                           {return FROM;}

<INITIAL>inject-with                    {return INJECTWITH;}

<INITIAL>of-kind                        {return OFKIND;}

<INITIAL>for				{return FOR;}

<INITIAL>if				{return IF;}

<INITIAL>else				{return ELSE;}

<INITIAL>while				{return WHILE;}

<INITIAL>break				{return BREAK;}

<INITIAL>continue                       {return CONTINUE;}

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

<INITIAL>"+"                            {return '+';}

<INITIAL>"-"                            {return '-';}

<INITIAL>"/"                            {return '/';}

<INITIAL>"<"                            {return '<';}

<INITIAL>">"                            {return '>';}

<INITIAL>"<="                           {return LE_OP;}

<INITIAL>">="                           {return GE_OP;}

<INITIAL>"("                            {return '(';}

<INITIAL>")"                            {return ')';}

<INITIAL>"["                            {return '[';}

<INITIAL>"]"                            {return ']';}

<INITIAL>"{"                            {return '{';}

<INITIAL>"}"                            {return '}';}

<INITIAL>"=="                           {return EQ_OP;}

<INITIAL>"!="                           {return NE_OP;}

<INITIAL>"&&"                           {return AND_OP;}

<INITIAL>"||"                           {return OR_OP;}

<INITIAL>{Identifier}                   {
                                            yylval = new_ptr(ast_symbol)(std::string(yytext, yyleng));
                                            return IDENTIFIER;
                                        }

<INITIAL>{IntegerLiteral}               {
                                            yylval = new_ptr(ast_constant)(atoll(yytext));
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
