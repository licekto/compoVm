%{
#include <iostream>
#include "parserWrapper.h"
#include "lexer.h"
#include "compoNode.h"
#include "compoSymbol.h"
#include "compoService.h"
#include "compoConstraint.h"
#include "compoPort.h"
#include "compoDescriptor.h"
#include "compoProvision.h"
#include "compoRequirement.h"
#include "compoFor.h"
#include "compoAssignment.h"
#include "visibilityType.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)

typedef struct sequence {
    std::vector<compo::CCompoNode*>    temporaries;
    std::vector<compo::CCompoNode*>    statements;

    void                        clear()     {temporaries.clear(); statements.clear();}
} TSEQUENCE;

std::vector<compo::CCompoNode*>     currentBody;
compo::CCompoService              * currentService      = nullptr;
std::vector<compo::CCompoSymbol*>   currentServiceParams;
std::vector<compo::CCompoNode*>     currentServiceBody;
TSEQUENCE                           currentSequence;

compo::visibilityType               visType             = compo::visibilityType::EXTERNAL;
bool                                atomicPresent       = false;
std::vector<compo::CCompoPort*>     currentPorts;

%}

%define api.value.type {compo::CCompoNode*}
%define parse.error verbose
%define parse.lac full

%debug

%parse-param {ParserWrapper* parser}

%start start

%token TOKEN_DESCRIPTOR
%token TOKEN_INTERFACE
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
%token TOKEN_INJECTWITH
%token TOKEN_OFKIND
%token TOKEN_FOR
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_WHILE
%token TOKEN_ASSIGNMENT
%token TOKEN_ASTERISK
%token TOKEN_AT
%token TOKEN_HASHTAG
%token TOKEN_DOT
%token TOKEN_COMMA
%token TOKEN_COLON
%token TOKEN_SEMICOLON
%token TOKEN_AMPERSAND
%token TOKEN_PIPE
%token TOKEN_DOLLAR
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_SLASH
%token TOKEN_APOSTROPHE
%token TOKEN_LESSTHAN
%token TOKEN_GREATERTHAN
%token TOKEN_OPENPAR
%token TOKEN_CLOSEPAR
%token TOKEN_OPENBRACKET
%token TOKEN_CLOSEBRACKET
%token TOKEN_OPENBRACE
%token TOKEN_CLOSEBRACE
%token TOKEN_IDENTIFIER
%token TOKEN_INTEGER_LITERAL;
%token TOKEN_END        0   "end of file"

%%

/*------------------------------- grammar ------------------------------------*/

array           :   TOKEN_OPENBRACE expressions TOKEN_CLOSEBRACE

assignment      :   variable TOKEN_ASSIGNMENT expression
                    {
                        compo::CCompoAssignment *assignment = new compo::CCompoAssignment(dynamic_cast<compo::CCompoSymbol*>($1), $2);
                        $$ = assignment;
                    }

expressions     :   expression TOKEN_SEMICOLON expressions
                |   /* epsilon */
                ;

expression      :   assignment /* cascadeExpression */
                    {
                        $$ = $1;
                    }
                |   variable
                    {
                        $$ = $1;
                    }
                ;

methodSequence  :   pragmas temporaries pragmas statements

parens          :   TOKEN_OPENPAR expression TOKEN_CLOSEPAR
                ;

statementsBody  :   TOKEN_OPENBRACE methodSequence TOKEN_CLOSEBRACE
                ;

forStatement    :   TOKEN_FOR TOKEN_OPENPAR expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON TOKEN_CLOSEPAR statementsBody
                    {
                        compo::CCompoFor *compoFor = new compo::CCompoFor();
                    }
                ;

whileStatement  :   TOKEN_WHILE parens statementsBody
                ;

ifStatement     :   TOKEN_IF parens statementsBody
                ;

else            :   TOKEN_ELSE statementsBody
                |   /* epsilon */
                ;

pragmas         :   pragma TOKEN_SEMICOLON pragmas
                |   /* epsilon */
                ;

pragma          :   TOKEN_LESSTHAN TOKEN_GREATERTHAN
                ;

return          :   TOKEN_RETURN expression
                ;

sequence        :   temporaries statements
                |   /* epsilon */
                ;

statements      :   statement statements
                    {
                        currentSequence.statements.push_back($1);
                    }
                |   /* epsilon */
                ;

statement       :   return TOKEN_SEMICOLON
                |   forStatement
                |   whileStatement
                |   ifStatement
                |   connectionDisconnection TOKEN_SEMICOLON
                |   expression TOKEN_SEMICOLON                  { $$ = $1; }
                ;

temporaries     :   TOKEN_PIPE variables TOKEN_PIPE
                    {
                        currentSequence.temporaries.push_back($2);
                    }
                |   /* epsilon */
                ;

variables       :   variable variables
                |   /* epsilon */
                ;

variable        :   TOKEN_IDENTIFIER
                    {
                        $$ = $1;
                    }
                ;

/*---------------------------- grammar-blocks --------------------------------*/

block           :   TOKEN_OPENBRACKET blockBody TOKEN_CLOSEBRACKET
                ;

blockBody       :   blockArgsSign sequence
                ;

blockArgsSign   :   blockArgumentsWith
                |   blockArgumentsWithout
                ;

blockArgumentsWith
                :   blockArguments TOKEN_PIPE
                ;

blockArgumentsWithout
                :   /* epsilon */
                ;

blockArguments  :   blockArgument blockArguments
                |   blockArgument
                ;

blockArgument   :   TOKEN_COLON variable
                ;

/*---------------------------- grammar-compo ---------------------------------*/

start           :   descriptorInterface TOKEN_END
                    {
                         YYACCEPT; return 0;
                    }
                ;

descriptorInterface
                :   descriptors
                |   interface
                ;
                    

descriptors     :   descriptor descriptors
                    {
                        parser->setRootNode($1);
                    }
                |   /* epsilon */
                ;

descriptor      :   TOKEN_DESCRIPTOR TOKEN_IDENTIFIER inheritance TOKEN_OPENBRACE compoExprs TOKEN_CLOSEBRACE
                    {
                        compo::CCompoDescriptor *descriptor = new compo::CCompoDescriptor(dynamic_cast<compo::CCompoSymbol*>($2), nullptr, std::move(currentBody));
                        if ($3) {
                            descriptor->setExtends(dynamic_cast<compo::CCompoSymbol*>($3));
                        }
                        currentBody.clear();
                        $$ = descriptor;
                    }

interface       :   TOKEN_INTERFACE TOKEN_IDENTIFIER inheritance servicesSignsList
                ;

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


compoExpr	:   exProvision
		|   exRequirement
		|   inProvision
		|   inRequirement
		|   constraint
		|   service
		|   architecture
                ;

exProvision     :   externally TOKEN_PROVIDES provReqSign
		    {
			currentBody.push_back(new compo::CCompoProvision(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

exRequirement   :   externally TOKEN_REQUIRES provReqSign
                    {
			currentBody.push_back(new compo::CCompoRequirement(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

provReqSign     :   TOKEN_OPENBRACE ports TOKEN_CLOSEBRACE
                ;

externally      :   TOKEN_EXTERNALLY	{visType = compo::visibilityType::EXTERNAL;}
                |   /* epsilon */
                ;

ports		:   port TOKEN_SEMICOLON ports
		|   /* epsilon */
		;

port		:   atomic TOKEN_IDENTIFIER brackets TOKEN_COLON portSign ofKind
		    {
			currentPorts.push_back(new compo::CCompoPort(dynamic_cast<compo::CCompoSymbol*>($2), atomicPresent));
		    }
		;

atomic		:   TOKEN_ATOMIC	{atomicPresent = true;}
		|   /* epsilon */	{atomicPresent = false;}
		;

brackets        :   TOKEN_OPENBRACKET TOKEN_CLOSEBRACKET
                |   /* epsilon */
                ;

portSign        :   TOKEN_IDENTIFIER
                |   TOKEN_ASTERISK
                |   servicesSignsList
                ;

ofKind          :   TOKEN_OFKIND TOKEN_IDENTIFIER
                |   /* epsilon */
                ;

service         :   TOKEN_SERVICE serviceSign TOKEN_OPENBRACE sequence TOKEN_CLOSEBRACE
                    {
                        currentBody.push_back(new compo::CCompoService(dynamic_cast<compo::CCompoSymbol*>($2), std::move(currentServiceParams), std::move(currentSequence.statements), std::move(currentSequence.temporaries)));
                        currentServiceParams.clear();
                        currentSequence.clear();
                    }
                ;

serviceSign     :   TOKEN_IDENTIFIER TOKEN_OPENPAR serviceParams TOKEN_CLOSEPAR
                    {
                        $$ = $1;
                    }
                ;

serviceSigns    :   serviceSign TOKEN_COMMA serviceSigns
                |   /* epsilon */
                ;

servicesSignsList
                :   TOKEN_OPENBRACE serviceSigns TOKEN_CLOSEBRACE

serviceParams   :   TOKEN_IDENTIFIER
                    {
                        currentServiceParams.push_back(dynamic_cast<compo::CCompoSymbol*>($1));
                    }
                |   TOKEN_IDENTIFIER TOKEN_COMMA serviceParams
                    {
                        currentServiceParams.push_back(dynamic_cast<compo::CCompoSymbol*>($1));
                    }
                |   /* epsilon */
                ;

constraint	:   TOKEN_CONSTRAINT serviceSign TOKEN_OPENBRACE TOKEN_CLOSEBRACE
                    {
                        currentBody.push_back(new compo::CCompoConstraint(dynamic_cast<compo::CCompoSymbol*>($2), std::move(currentServiceParams), currentServiceBody));
                        currentServiceParams.clear();
                    }
		;

inRequirement   :   internally TOKEN_REQUIRES TOKEN_OPENBRACE injectPorts TOKEN_CLOSEBRACE
		;

inProvision	:   internally TOKEN_PROVIDES provReqSign
                    {
			currentBody.push_back(new compo::CCompoRequirement(visType, std::move(currentPorts)));
			currentPorts.clear();
                        visType = compo::visibilityType::EXTERNAL;
		    }
		;

injectPorts     :   injectPort TOKEN_SEMICOLON injectPorts
                |   /* epsilon */
                ;

injectPort      :   port inject
                ;

inject          :   TOKEN_INJECTWITH TOKEN_IDENTIFIER
                |   /* epsilon */
                ;

internally      :   TOKEN_INTERNALLY	{visType = compo::visibilityType::INTERNAL;}
                |   /* epsilon */
                ;

architecture	:   TOKEN_ARCHITECTURE TOKEN_OPENBRACE connectionDisconnection TOKEN_CLOSEBRACE
		;

connectionDisconnection
                :   connections
                |   disconnections
                ;

connections     :   connection TOKEN_SEMICOLON connections 
                |   /* epsilon */
                ;

connection      :   TOKEN_CONNECT
                ;

disconnections  :   disconnection TOKEN_SEMICOLON disconnections
                |   /* epsilon */
                ;

disconnection   :
                ;

/*-------------------------- grammar-literals-compo --------------------------*/

collectionPortLiteral
                :   TOKEN_IDENTIFIER TOKEN_OPENBRACKET expression TOKEN_CLOSEBRACKET
                ;

dereferenceLiteral
                :   TOKEN_AMPERSAND TOKEN_IDENTIFIER
                ;

portAddressLiteral
                :   TOKEN_IDENTIFIER TOKEN_AT 
                ;

portAddress     :   collectionPortLiteral
                |   TOKEN_OPENPAR /* cascadeExpression */ TOKEN_CLOSEPAR
                |   dereferenceLiteral
                |   TOKEN_IDENTIFIER
                ;

/*----------------------------------------------------------------------------*/
%%

void ParserWrapper::error(const std::string& message) {
    std::cerr << message << std::endl;
}

int ParserWrapper::parse(std::istream& is) {

    m_lexer->switch_streams(&is, &std::cout);
    m_lexer->resetState();

    return yyparse(this);
}

void ParserWrapper::parseAll(std::istream& is) {

    m_lexer->switch_streams(&is, &std::cout);
    m_lexer->resetState();

    while(1) {
        if (!yyparse(this)) {
            break;
        }
    }
}