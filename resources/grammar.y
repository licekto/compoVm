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

%token DESCRIPTOR
%token INTERFACE
%token EXTENDS
%token ARCHITECTURE
%token CONSTRAINT
%token SERVICE
%token INTERNALLY
%token EXTERNALLY
%token PROVIDES
%token REQUIRES
%token ATOMIC
%token CONNECT
%token DISCONNECT
%token DELEGATE
%token RETURN
%token TO
%token INJECTWITH
%token OFKIND
%token FOR
%token IF
%token ELSE
%token WHILE
%token ASSIGNMENT
%token ADD_ASSIGNMENT;
%token IDENTIFIER
%token INTEGER_LITERAL;
%token END

%%

/*-------------------------- grammar-procedural ------------------------------*/

array
                :   '{' expression '}'
                ;

primary_expression
                :   IDENTIFIER
                |   INTEGER_LITERAL
                |   '(' expression ')'
                ;

multiplicative_expression
                : primary_expression
                | multiplicative_expression '*' primary_expression
                | multiplicative_expression '/' primary_expression
                ;

additive_expression
                : multiplicative_expression
                | additive_expression '+' multiplicative_expression
                | additive_expression '-' multiplicative_expression
                ;

assignment_expression
                :   additive_expression
                |   primary_expression assignment_operator expression
                    {
                        compo::CCompoAssignment *assignment = new compo::CCompoAssignment(dynamic_cast<compo::CCompoSymbol*>($1), $3);
                        $$ = assignment;
                    }

assignment_operator
                : ASSIGNMENT
                | ADD_ASSIGNMENT
                ;

expression      
                :   assignment_expression
                    {
                        $$ = $1;
                    }
                |   expression ',' assignment_expression
                ;

declaration
                :   assignment_expression
                ;



statement
                :   compound_statement
                |   expression_statement
                |   selection_statement
                |   iteration_statement
                |   jump_statement
                ;

compound_statement
                :   '{' '}'
                |   '{' block_item_list '}'

block_item_list
                : block_item
                | block_item_list block_item
                ;

block_item
                : declaration
                | statement
                ;

expression_statement
                :   ';'
                |   expression ';'
                ;

selection_statement
                :   IF '(' expression ')' statement
                |   IF '(' expression ')' statement ELSE statement
                ;

iteration_statement
                : FOR '(' expression_statement expression_statement ')' statement
                | FOR '(' expression_statement expression_statement expression ')' statement
                | FOR '(' declaration expression_statement ')' statement
                | FOR '(' declaration expression_statement expression ')' statement
                ;

jump_statement
                : RETURN expression ';'
                ;

/*---------------------------- grammar-compo ---------------------------------*/

start           
                :   descriptorInterface END
                    {
                         YYACCEPT; return 0;
                    }
                ;

descriptorInterface
                :   descriptors
                |   interface
                ;
                    

descriptors     
                :   descriptor descriptors
                    {
                        parser->setRootNode($1);
                    }
                |   /* epsilon */
                ;

descriptor      
                :   DESCRIPTOR IDENTIFIER inheritance '{' compoExprs '}'
                    {
                        compo::CCompoDescriptor *descriptor = new compo::CCompoDescriptor(dynamic_cast<compo::CCompoSymbol*>($2), nullptr, std::move(currentBody));
                        if ($3) {
                            descriptor->setExtends(dynamic_cast<compo::CCompoSymbol*>($3));
                        }
                        currentBody.clear();
                        $$ = descriptor;
                    }

interface       
                :   INTERFACE IDENTIFIER inheritance servicesSignsList
                ;

inheritance     
                :   EXTENDS IDENTIFIER
                    {
                        $$ = $2;
                    }
                |   /* epsilon */
                    {$$ = nullptr;}
                ;

compoExprs      
                :   compoExpr compoExprs
                |   /* epsilon */
                ;


compoExpr	
                :   exProvision
		|   exRequirement
		|   inProvision
		|   inRequirement
		|   constraint
		|   service
		|   architecture
                ;

exProvision     
                :   externally PROVIDES provReqSign
		    {
			currentBody.push_back(new compo::CCompoProvision(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

exRequirement   
                :   externally REQUIRES provReqSign
                    {
			currentBody.push_back(new compo::CCompoRequirement(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

provReqSign     
                :   '{' ports '}'
                ;

externally      
                :   EXTERNALLY
                    {visType = compo::visibilityType::EXTERNAL;}
                |   /* epsilon */
                ;

ports		
                :   port ';' ports
		|   /* epsilon */
		;

port		
                :   atomic IDENTIFIER brackets ':' portSign ofKind
		    {
			currentPorts.push_back(new compo::CCompoPort(dynamic_cast<compo::CCompoSymbol*>($2), atomicPresent));
		    }
		;

atomic		
                :   ATOMIC
                    {atomicPresent = true;}
		|   /* epsilon */
                    {atomicPresent = false;}
		;

brackets        
                :   '[' ']'
                |   /* epsilon */
                ;

portSign        
                :   IDENTIFIER
                |   '*'
                |   servicesSignsList
                ;

ofKind          
                :   OFKIND IDENTIFIER
                |   /* epsilon */
                ;

service         
                :   SERVICE serviceSign block_item_list
                    {
                        currentBody.push_back(new compo::CCompoService(dynamic_cast<compo::CCompoSymbol*>($2), std::move(currentServiceParams), std::move(currentSequence.statements), std::move(currentSequence.temporaries)));
                        currentServiceParams.clear();
                        currentSequence.clear();
                    }
                ;

serviceSign     
                :   IDENTIFIER '(' serviceParams ')'
                    {
                        $$ = $1;
                    }
                ;

serviceSigns    
                :   serviceSign ',' serviceSigns
                |   /* epsilon */
                ;

servicesSignsList
                :   '{' serviceSigns '}'

serviceParams   
                :   IDENTIFIER
                    {
                        currentServiceParams.push_back(dynamic_cast<compo::CCompoSymbol*>($1));
                    }
                |   IDENTIFIER ',' serviceParams
                    {
                        currentServiceParams.push_back(dynamic_cast<compo::CCompoSymbol*>($1));
                    }
                |   /* epsilon */
                ;

constraint	
                :   CONSTRAINT serviceSign '{' '}'
                    {
                        currentBody.push_back(new compo::CCompoConstraint(dynamic_cast<compo::CCompoSymbol*>($2), std::move(currentServiceParams), currentServiceBody));
                        currentServiceParams.clear();
                    }
		;

inRequirement   
                :   internally REQUIRES '{' injectPorts '}'
		;

inProvision	
                :   internally PROVIDES provReqSign
                    {
			currentBody.push_back(new compo::CCompoRequirement(visType, std::move(currentPorts)));
			currentPorts.clear();
                        visType = compo::visibilityType::EXTERNAL;
		    }
		;

injectPorts     
                :   injectPort ';' injectPorts
                |   /* epsilon */
                ;

injectPort      
                :   port inject
                ;

inject          
                :   INJECTWITH IDENTIFIER
                |   /* epsilon */
                ;

internally      
                :   INTERNALLY
                    {visType = compo::visibilityType::INTERNAL;}
                |   /* epsilon */
                ;

architecture	
                :   ARCHITECTURE '{' connectionDisconnection '}'
		;

connectionDisconnection
                :   connections
                |   disconnections
                ;

connections     
                :   connection ';' connections 
                |   /* epsilon */
                ;

connection      
                :   CONNECT
                ;

disconnections  
                :   disconnection ';' disconnections
                |   /* epsilon */
                ;

disconnection   
                :
                ;

/*-------------------------- grammar-literals-compo --------------------------*/

collectionPortLiteral
                :   IDENTIFIER '[' expression ']'
                ;

dereferenceLiteral
                :   '&' IDENTIFIER
                ;

portAddressLiteral
                :   IDENTIFIER '@'
                ;

portAddress     :   collectionPortLiteral
                |   '(' /* cascadeExpression */ ')'
                |   dereferenceLiteral
                |   IDENTIFIER
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