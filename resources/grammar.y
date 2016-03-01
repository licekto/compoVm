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
#include "nodes/procedural/forStatement.h"
#include "nodes/procedural/whileStatement.h"
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
#include "nodes/procedural/lessExpression.h"
#include "nodes/procedural/lessOrEqualExpression.h"
#include "nodes/procedural/greaterExpression.h"
#include "nodes/procedural/greaterOrEqualExpression.h"

#include "nodes/procedural/constant.h"
#include "nodes/procedural/parens.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)

std::shared_ptr<TBLOCK> currentBlock = std::make_shared<TBLOCK>();
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
%token GE_OP
%token LE_OP
%token AND_OP
%token OR_OP
%token BREAK
%token CONTINUE
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

relational_expression
                :   additive_expression
                    {
                        $$ = $1;
                    }
                |   relational_expression '<' additive_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CLessExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                |   relational_expression '>' additive_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CGreaterExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                |   relational_expression LE_OP additive_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CLessOrEqualExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                |   relational_expression GE_OP additive_expression
                    {
                        $$ = std::make_shared<nodes::procedural::CGreaterOrEqualExpression>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;

equality_expression
                :   relational_expression
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
                :   logical_or_expression
                    {
                        $$ = $1;
                    }
                |   primary_expression ASSIGNMENT expression
                    {
                        $$ = std::make_shared<nodes::procedural::CAssignmentExpression>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1), $3);
                    }

expression      
                :   assignment_expression
                    {
                        $$ = $1;
                    }
                |   expression ',' assignment_expression
                ;

statement
                :   compound_statement
                    {
                        $$ = $1;
                    }
                |   expression_statement
                    {
                        $$ = $1;
                    }
                |   selection_statement
                    {
                        $$ = $1;
                    }
                |   iteration_statement
                    {
                        $$ = $1;
                    }
                |   jump_statement
                    {
                        $$ = $1;
                    }
                ;

compound_statement
                :   '{' '}'
                |   '{' temporaries statement_list '}'
                    {
                        parser->pushBlock(currentBlock);
                        currentBlock.reset();
                        currentBlock = std::make_shared<TBLOCK>();
                    }
                ;

temporaries
                :   '|' temporaries_list '|'
                |   /* epsilon */
                ;

temporaries_list
                :   IDENTIFIER
                    {
                        currentBlock->temporaries.push_back(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                |   temporaries_list IDENTIFIER
                    {
                        currentBlock->temporaries.push_back(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2));
                    }
                ;

statement_list
                :   statement
                    {
                        currentBlock.statements.push_back($1);
                    }
                |   statement_list statement
                    {
                        currentBlock.statements.push_back($2);
                    }
                ;

expression_statement
                :   ';'
                |   expression ';'
                    {
                        $$ = $1;
                    }
                ;

selection_statement
                :   IF '(' expression ')' statement
                |   IF '(' expression ')' statement ELSE statement
                ;

iteration_statement
                :   WHILE '(' expression ')' statement
                    {
                        $$ = std::make_shared<nodes::procedural::CWhileStatement>(  std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3),
                                                                                    std::make_shared<nodes::procedural::CCompoundBody>(currentBlock.temporaries, currentBlock.statements));
                        currentBlock.clear();
                    }
                |   FOR '(' assignment_expression expression_statement expression ')' statement
                    {
                        $$ = std::make_shared<nodes::procedural::CForStatement>(std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>($3),
                                                                                std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($4),
                                                                                std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($5),
                                                                                std::make_shared<nodes::procedural::CCompoundBody>(currentBlock.temporaries, currentBlock.statements));
                        currentBlock.clear();
                    }
                ;

jump_statement
                :   CONTINUE ';'
                |   BREAK ';'
                |   RETURN expression ';'
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
                    {
                        $$ = nullptr;
                    }
                ;

compoExprs      
                :   compoExpr compoExprs
                |   /* epsilon */           // Empty descriptor allowed
                ;


compoExpr	
                :   provision
		|   requirement
		|   constraint
		|   service
		|   architecture
                ;

provision     
                :   visibility PROVIDES provReqSign
		    {
			currentBody.push_back(std::make_shared<nodes::compo::CProvision>(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

requirement   
                :   visibility REQUIRES provReqSign
                    {
			currentBody.push_back(std::make_shared<nodes::compo::CRequirement>(visType, std::move(currentPorts)));
			currentPorts.clear();
		    }
                ;

visibility
                :   EXTERNALLY
                    {
                        visType = nodes::types::visibilityType::EXTERNAL;
                    }
                |   INTERNALLY
                    {
                        visType = nodes::types::visibilityType::INTERNAL;
                    }
                |   /* epsilon */
                    {
                        visType = nodes::types::visibilityType::EXTERNAL;
                    }
                ;

provReqSign     
                :   '{' ports '}'
                ;

ports		
                :   port ';'
                |   port ';' ports
		;

port		
                :   atomic IDENTIFIER brackets ':' portSign ofKind
		    {
			currentPorts.push_back(std::make_shared<nodes::compo::CPort>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), atomicPresent));
		    }
		;

atomic		
                :   ATOMIC
                    {
                        atomicPresent = true;
                    }
		|   /* epsilon */
                    {
                        atomicPresent = false;
                    }
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
                        //currentBody.push_back(std::make_shared<nodes::compo::CService>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), std::move(currentServiceParams), std::move(currentBlock.statements), std::move(currentBlock.temporaries)));
                        //currentServiceParams.clear();
                        //currentBlock.clear();
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
                        //currentServiceParams.push_back(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                |   IDENTIFIER ',' serviceParams
                    {
                        //currentServiceParams.push_back(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                |   /* epsilon */
                ;

constraint	
                :   CONSTRAINT serviceSign '{' '}'
                    {
                        //currentBody.push_back(std::make_shared<nodes::compo::CConstraint>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2), std::move(currentServiceParams), currentServiceBody));
                        //currentServiceParams.clear();
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