%{
#include <iostream>
#include <memory>

#include "parser/parserWrapper.h"
#include "parser/lexer.h"
#include "nodes/node.h"
#include "nodes/types/visibilityType.h"
#include "nodes/compo/service.h"
#include "nodes/compo/constraint.h"
#include "nodes/compo/port.h"
#include "nodes/compo/descriptor.h"
#include "nodes/compo/provision.h"
#include "nodes/compo/requirement.h"
#include "nodes/procedural/symbol.h"
#include "nodes/procedural/for.h"
#include "nodes/procedural/abstractExpression.h"
#include "nodes/procedural/assignmentExpression.h"
#include "nodes/procedural/additionExpression.h"
#include "nodes/procedural/subtractionExpression.h"
#include "nodes/procedural/multiplicationExpression.h"
#include "nodes/procedural/divisionExpression.h"
#include "nodes/procedural/equalityExpression.h"
#include "nodes/procedural/nonEqualityExpression.h"
#include "nodes/procedural/logicalAndExpression.h"
#include "nodes/procedural/logicalOrExpression.h"

#include "nodes/procedural/constant.h"
#include "nodes/procedural/parens.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)

typedef struct block {
    std::vector<std::shared_ptr<nodes::CNode>>    temporaries;
    std::vector<std::shared_ptr<nodes::CNode>>    statements;

    void                        clear()     {temporaries.clear(); statements.clear();}
} TBLOCK;

std::vector<std::shared_ptr<nodes::CNode>>                  currentBody;
std::shared_ptr<nodes::compo::CService>                     currentService          = nullptr;
std::vector<std::shared_ptr<nodes::procedural::CSymbol>>    currentServiceParams;
std::vector<std::shared_ptr<nodes::CNode>>                  currentServiceBody;
TBLOCK                                                      currentBlock;

nodes::types::visibilityType                                visType                 = nodes::types::visibilityType::EXTERNAL;
bool                                                        atomicPresent           = false;
std::vector<std::shared_ptr<nodes::compo::CPort>>           currentPorts;

%}

%define api.value.type {std::shared_ptr<nodes::CNode>}
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
%token EQ_OP
%token NE_OP
%token AND_OP
%token OR_OP
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
                        $$ = std::make_shared<nodes::procedural::CParens>($2);
                    }
                ;

multiplicative_expression
                :   primary_expression
                    {
                        $$ = $1;
                    }
                |   multiplicative_expression '*' primary_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CMultiplicationExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                |   multiplicative_expression '/' primary_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CDivisionExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;

additive_expression
                :   multiplicative_expression
                    {
                        $$ = $1;
                    }
                |   additive_expression '+' multiplicative_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CAdditionExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                |   additive_expression '-' multiplicative_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CSubtractionExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;

equality_expression
                :   additive_expression
                    {
                        $$ = $1;
                    }
                |   equality_expression EQ_OP additive_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CEqualityExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                |   equality_expression NE_OP additive_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CNonEqualityExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;

logical_and_expression
                :   equality_expression
                    {
                        $$ = $1;
                    }
                |   logical_and_expression AND_OP equality_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CLogicalAndExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;

logical_or_expression
                :   logical_and_expression
                    {
                        $$ = $1;
                    }
                |   logical_or_expression OR_OP logical_and_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CLogicalOrExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;


assignment_expression
                :   logical_and_expression
                    {
                        $$ = $1;
                    }
                |   primary_expression assignment_operator expression
                    {
                        $$ = std::make_shared<nodes::procedural::CAssignmentExpression>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1), $3);
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
                        $$ = std::make_shared<nodes::compo::CDescriptor>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), std::dynamic_pointer_cast<nodes::procedural::CSymbol>($3), std::move(currentBody));
                        currentBody.clear();
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
			currentBody.push_back(std::make_shared<nodes::compo::CProvision>(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

exRequirement   
                :   externally REQUIRES provReqSign
                    {
			currentBody.push_back(std::make_shared<nodes::compo::CRequirement>(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

provReqSign     
                :   '{' ports '}'
                ;

externally      
                :   EXTERNALLY
                    {visType = nodes::types::visibilityType::EXTERNAL;}
                |   /* epsilon */
                ;

ports		
                :   port ';' ports
		|   /* epsilon */
		;

port		
                :   atomic IDENTIFIER brackets ':' portSign ofKind
		    {
			currentPorts.push_back(std::make_shared<nodes::compo::CPort>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), atomicPresent));
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
                        currentBody.push_back(std::make_shared<nodes::compo::CService>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), std::move(currentServiceParams), std::move(currentBlock.statements), std::move(currentBlock.temporaries)));
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
                        currentServiceParams.push_back(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                |   IDENTIFIER ',' serviceParams
                    {
                        currentServiceParams.push_back(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                |   /* epsilon */
                ;

constraint	
                :   CONSTRAINT serviceSign '{' '}'
                    {
                        currentBody.push_back(std::make_shared<nodes::compo::CConstraint>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), std::move(currentServiceParams), currentServiceBody));
                        currentServiceParams.clear();
                    }
		;

inRequirement   
                :   internally REQUIRES '{' injectPorts '}'
		;

inProvision	
                :   internally PROVIDES provReqSign
                    {
			currentBody.push_back(std::make_shared<nodes::compo::CRequirement>(visType, std::move(currentPorts)));
                        currentPorts.clear();
                        visType = nodes::types::visibilityType::EXTERNAL;
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
                    {
                        visType = nodes::types::visibilityType::INTERNAL;
                    }
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