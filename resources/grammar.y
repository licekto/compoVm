%{
#include <iostream>
#include "parser/parserWrapper.h"
#include "parser/lexer.h"
#include "nodes/compoNode.h"
#include "nodes/proceduralNodes/compoSymbol.h"
#include "nodes/compoNodes/compoService.h"
#include "nodes/compoNodes/compoConstraint.h"
#include "nodes/compoNodes/compoPort.h"
#include "nodes/compoNodes/compoDescriptor.h"
#include "nodes/compoNodes/compoProvision.h"
#include "nodes/compoNodes/compoRequirement.h"
#include "nodes/proceduralNodes/compoFor.h"
#include "nodes/proceduralNodes/compoAssignment.h"
#include "nodes/compoTypes/visibilityType.h"
#include "nodes/proceduralNodes/compoConstant.h"
#include "nodes/proceduralNodes/compoParens.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)

typedef struct block {
    std::vector<compo::CCompoNode*>    temporaries;
    std::vector<compo::CCompoNode*>    statements;

    void                        clear()     {temporaries.clear(); statements.clear();}
} TBLOCK;

std::vector<compo::CCompoNode*>     currentBody;
compo::CCompoService              * currentService      = nullptr;
std::vector<compo::CCompoSymbol*>   currentServiceParams;
std::vector<compo::CCompoNode*>     currentServiceBody;
TBLOCK                              currentBlock;

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
%token ADD_ASSIGNMENT
%token IDENTIFIER
%token CONSTANT
%token STRING_LITERAL
%token END

%%

/*-------------------------- grammar-procedural ------------------------------*/

array
                :   '{' expression '}'
                ;

primary_expression
                :   IDENTIFIER
                    {
                        $$ = $1;
                    }
                |   CONSTANT
                    {
                        $$ = $1;
                    }
                |   STRING_LITERAL
                    {
                        $$ = $1;
                    }
                |   '(' expression ')'
                    {
                        $$ = new compo::CCompoParens($2);
                    }
                ;

multiplicative_expression
                :   primary_expression
                    {
                        $$ = $1;
                    }
                |   multiplicative_expression '*' primary_expression
                |   multiplicative_expression '/' primary_expression
                ;

additive_expression
                :   multiplicative_expression
                    {
                        $$ = $1;
                    }
                |   additive_expression '+' multiplicative_expression
                |   additive_expression '-' multiplicative_expression
                ;

assignment_expression
                :   additive_expression
                    {
                        $$ = $1;
                    }
                |   primary_expression assignment_operator expression
                    {
                        $$ = new compo::CCompoAssignment(dynamic_cast<compo::CCompoSymbol*>($1), $3);
                    }

assignment_operator
                :   ASSIGNMENT
                |   ADD_ASSIGNMENT
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
                    {
                        $$ = $1;
                    }
                ;



statement
                :   expression_statement
                |   selection_statement
                |   iteration_statement
                |   jump_statement
                ;

compound_statement
                :   '{' '}'
                |   '{' block_item_list '}'
                    {
                        $$ = $1;
                    }

block_item_list
                :   block_item
                    {
                        currentBlock.statements.push_back($1);
                    }
                |   block_item_list block_item
                    {
                        currentBlock.statements.push_back($2);
                    }
                ;

block_item
                :   declaration
                    {
                        $$ = $1;
                    }
                |   statement
                    {
                        $$ = $1;
                    }
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
                :   FOR '(' expression_statement expression_statement ')' statement
                |   FOR '(' expression_statement expression_statement expression ')' statement
                |   FOR '(' declaration expression_statement ')' statement
                |   FOR '(' declaration expression_statement expression ')' statement
                ;

jump_statement
                :   RETURN expression ';'
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
                :   SERVICE serviceSign compound_statement
                    {
                        currentBody.push_back(new compo::CCompoService(dynamic_cast<compo::CCompoSymbol*>($2), std::move(currentServiceParams), std::move(currentBlock.statements), std::move(currentBlock.temporaries)));
                        currentServiceParams.clear();
                        currentBlock.clear();
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