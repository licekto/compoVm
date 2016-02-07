%{
#include <iostream>
#include "parserWrapper.h"
#include "lexer.h"
#include "compoNode.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)

CCompoNode *root = nullptr;

NODE_VECTOR currentBody;

CCompoService * currentService = nullptr;
SYMBOL_VECTOR currentServiceParams;
NODE_VECTOR currentServiceBody;

bool externallyPresent = false;
bool atomicPresent = false;
PORT_VECTOR currentPorts;

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
%token TOKEN_DELEGATE
%token TOKEN_RETURN
%token TOKEN_TO
%token TOKEN_AT
%token TOKEN_ASSIGN
%token TOKEN_DOT
%token TOKEN_COMMA
%token TOKEN_OPENBRACE
%token TOKEN_CLOSEBRACE
%token TOKEN_OPENPAR
%token TOKEN_CLOSEPAR
%token TOKEN_COLON
%token TOKEN_SEMICOLON
%token TOKEN_PIPE
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
                |   /* epsilon */
                ;

compoExpr       :   service
                |   exRequirements
                |   exProvisions
                ;

exProvisions    :   externally TOKEN_PROVIDES TOKEN_OPENBRACE ports TOKEN_CLOSEBRACE
		    {
			currentBody.push_back(new CCompoProvision(externallyPresent, currentPorts));
			currentPorts.clear();
		    }
                ;

ports		:   port ports
		|   /* epsilon */
		;

port		:   atomic TOKEN_IDENTIFIER TOKEN_COLON TOKEN_OPENBRACE TOKEN_CLOSEBRACE
		    {
			currentPorts.push_back(new CCompoPort((CCompoSymbol*) $2, atomicPresent));
		    }
		;

atomic		:   TOKEN_ATOMIC	{atomicPresent = true;}
		|   /* epsilon */	{atomicPresent = false;}
		;

exRequirements  :   externally TOKEN_REQUIRES TOKEN_IDENTIFIER TOKEN_OPENBRACE TOKEN_CLOSEBRACE
                ;

externally      :   TOKEN_EXTERNALLY	{externallyPresent = true;}
                |   /* epsilon */	{externallyPresent = false;}
                ;

service         :   TOKEN_SERVICE TOKEN_IDENTIFIER TOKEN_OPENPAR serviceParams TOKEN_CLOSEPAR TOKEN_OPENBRACE TOKEN_CLOSEBRACE
                    {
                        currentBody.push_back(new CCompoService((CCompoSymbol*) $2, currentServiceParams, currentServiceBody));
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