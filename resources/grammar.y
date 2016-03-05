%{
#include <iostream>
#include <memory>

#include "parser/parserWrapper.h"
#include "parser/lexer.h"
#include "nodes/node.h"
#include "nodes/types/visibilityType.h"
#include "nodes/types/portType.h"
#include "nodes/compo/architecture.h"
#include "nodes/compo/service.h"
#include "nodes/compo/dereferenceLiteral.h"
#include "nodes/compo/collectionPortLiteral.h"
#include "nodes/compo/constraint.h"
#include "nodes/compo/connection.h"
#include "nodes/compo/disconnection.h"
#include "nodes/compo/port.h"
#include "nodes/compo/portAddress.h"
#include "nodes/compo/namedPort.h"
#include "nodes/compo/signaturesPort.h"
#include "nodes/compo/universalPort.h"
#include "nodes/compo/descriptor.h"
#include "nodes/compo/provision.h"
#include "nodes/compo/requirement.h"
#include "nodes/compo/serviceSignature.h"
#include "nodes/compo/serviceInvocation.h"
#include "nodes/compo/bind.h"
#include "nodes/procedural/symbol.h"
#include "nodes/procedural/ifStatement.h"
#include "nodes/procedural/forStatement.h"
#include "nodes/procedural/whileStatement.h"
#include "nodes/procedural/breakStatement.h"
#include "nodes/procedural/continueStatement.h"
#include "nodes/procedural/returnStatement.h"
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
%token FROM
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
                    {
                        $$ = $1;
                    }
                ;

statement
                :   expression_statement
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
                |   compound_statement
                    {
                        $$ = $1;
                    }
                ;

compound_statement
                :   push_context '{' temporaries statement_list '}'
                    {
                        $$ = parser->getCurrentCompoundBody();
                        parser->setCurrentCompoundBody(parser->popBlock());
                    }
                ;

push_context
                :   {
                        parser->pushBlock(parser->getCurrentCompoundBody());
                        parser->setCurrentCompoundBody(std::make_shared<nodes::procedural::CCompoundBody>());
                    }
                ;

temporaries
                :   '|' temporaries_list '|'
                |   /* epsilon */
                ;

temporaries_list
                :   IDENTIFIER
                    {
                        parser->getCurrentCompoundBody()->addTemporary(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                |   temporaries_list IDENTIFIER
                    {
                        parser->getCurrentCompoundBody()->addTemporary(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2));
                    }
                ;

statement_list
                :   statement
                    {
                        parser->getCurrentCompoundBody()->addBodyNode($1);
                    }
                |   statement_list statement
                    {
                        parser->getCurrentCompoundBody()->addBodyNode($2);
                    }
                |   /* epsilon */
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
                    {
                        $$ = std::make_shared<nodes::procedural::CIfStatement>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3),
                                                                               std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($5),
                                                                               nullptr);
                    }
                |   IF '(' expression ')' statement ELSE statement
                    {
                        $$ = std::make_shared<nodes::procedural::CIfStatement>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3),
                                                                               std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($5),
                                                                               std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($7));
                    }
                ;

iteration_statement
                :   WHILE '(' expression ')' statement
                    {
                        $$ = std::make_shared<nodes::procedural::CWhileStatement>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3),
                                                                                  std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($5));
                    }
                |   FOR '(' assignment_expression ';' expression_statement expression ')' statement
                    {
                        $$ = std::make_shared<nodes::procedural::CForStatement>(std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>($3),
                                                                                std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($5),
                                                                                std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($6),
                                                                                std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($8));
                    }
                ;

jump_statement
                :   CONTINUE ';'
                    {
                        $$ = std::make_shared<nodes::procedural::CContinueStatement>();
                    }
                |   BREAK ';'
                    {
                        $$ = std::make_shared<nodes::procedural::CBreakStatement>();
                    }
                |   RETURN expression ';'
                    {
                        $$ = std::make_shared<nodes::procedural::CReturnStatement>(std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($2));
                    }
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
                        $$ = std::make_shared<nodes::compo::CDescriptor>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2),
                                                                         std::dynamic_pointer_cast<nodes::procedural::CSymbol>($3),
                                                                         std::move(*(parser->getDescriptorBody())));
                        parser->clearAll();
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
			parser->addDescriptorBodyNode(std::make_shared<nodes::compo::CProvision>(parser->getVisibility(), *parser->getPorts()));
                        parser->clearPorts();
		    }
                ;

requirement   
                :   visibility REQUIRES provReqSign
                    {
			parser->addDescriptorBodyNode(std::make_shared<nodes::compo::CRequirement>(parser->getVisibility(), *parser->getPorts()));
                        parser->clearPorts();
		    }
                ;

visibility
                :   EXTERNALLY
                    {
                        parser->setVisibility(nodes::types::visibilityType::EXTERNAL);
                    }
                |   INTERNALLY
                    {
                        parser->setVisibility(nodes::types::visibilityType::INTERNAL);
                    }
                |   /* epsilon */
                    {
                        parser->setVisibility(nodes::types::visibilityType::EXTERNAL);
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
                :   atomic portName collecting ':' portSign ofKind
		    {
                        std::dynamic_pointer_cast<nodes::compo::CPort>($5)->setKindOf(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($6));
			parser->addPort(std::dynamic_pointer_cast<nodes::compo::CPort>($5));
		    }
		;

atomic		
                :   ATOMIC
                    {
                        parser->setAtomicity(true);
                    }
		|   /* epsilon */
                    {
                        parser->setAtomicity(false);
                    }
		;

portName
                :   IDENTIFIER
                    {
                        parser->setPortName(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                ;

collecting        
                :   '[' ']'
                    {
                        parser->setCollectivity(true);
                    }
                |   /* epsilon */
                    {
                        parser->setCollectivity(false);
                    }
                ;

portSign        
                :   IDENTIFIER
                    {
                        $$ = std::make_shared<nodes::compo::CNamedPort>(parser->getPortName(),
                                                                        parser->getAtomicity(),
                                                                        std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1),
                                                                        parser->getCollectivity());
                    }
                |   '*'
                    {
                        $$ = std::make_shared<nodes::compo::CUniversalPort>(parser->getPortName(),
                                                                            parser->getAtomicity(),
                                                                            parser->getCollectivity());
                    }
                |   servicesSignsList
                    {
                        $$ = std::make_shared<nodes::compo::CSignaturesPort>(parser->getPortName(),
                                                                             parser->getAtomicity(),
                                                                            *parser->getServiceSignatures(),
                                                                             parser->getCollectivity());
                        parser->clearServiceSignatures();
                    }
                ;

ofKind          
                :   OFKIND IDENTIFIER
                    {
                        $$ = $2;
                    }
                |   /* epsilon */
                    {
                        $$ = nullptr;
                    }
                ;

service         
                :   SERVICE serviceSign compound_statement
                    {
                        parser->addDescriptorBodyNode(std::make_shared<nodes::compo::CService>(std::dynamic_pointer_cast<nodes::compo::CServiceSignature>($2),
                                                                                               std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($3)));
                    }
                ;

serviceSign     
                :   IDENTIFIER '(' serviceParams ')'
                    {
                        $$ = std::make_shared<nodes::compo::CServiceSignature>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1), *parser->getServiceParams());
                        parser->clearServiceParams();
                    }
                ;

serviceSigns    
                :   serviceSign
                    {
                        parser->addServiceSignature(std::dynamic_pointer_cast<nodes::compo::CServiceSignature>($1));
                    }
                |   serviceSign ';' serviceSigns
                    {
                        parser->addServiceSignature(std::dynamic_pointer_cast<nodes::compo::CServiceSignature>($1));
                    }
                |   /* epsilon */
                ;

servicesSignsList
                :   '{' serviceSigns '}'

serviceParams   
                :   param
                |   param ',' serviceParams
                |   /* epsilon */
                ;

param
                :   IDENTIFIER
                    {
                        parser->addServiceParam(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1));
                    }
                ;

constraint	
                :   CONSTRAINT serviceSign compound_statement
                    {
                        parser->addDescriptorBodyNode(std::make_shared<nodes::compo::CConstraint>(std::dynamic_pointer_cast<nodes::compo::CServiceSignature>($2),
                                                                                                  std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>($3)));
                    }
		;

architecture	
                :   ARCHITECTURE '{' connectionDisconnection '}'
                    {
                        parser->addDescriptorBodyNode(std::make_shared<nodes::compo::CArchitecture>(*parser->getArchitectureBody()));
                        parser->clearArchitectureBody();
                    }
		;

connectionDisconnection
                :   connections
                |   disconnections
                ;

connections     
                :   connection ';' connections
                    {
                        parser->addArchitectureNode(std::dynamic_pointer_cast<nodes::compo::CBind>($1));
                    }
                |   /* epsilon */
                ;

connection      
                :   CONNECT portAddress TO portAddress
                    {
                        $$ = std::make_shared<nodes::compo::CConnection>(std::dynamic_pointer_cast<nodes::compo::CPortAddress>($2), std::dynamic_pointer_cast<nodes::compo::CPortAddress>($4));
                    }
                ;

disconnections  
                :   disconnection ';' disconnections
                    {
                        parser->addArchitectureNode(std::dynamic_pointer_cast<nodes::compo::CBind>($1));
                    }
                |   /* epsilon */
                ;

disconnection   
                :   DISCONNECT portAddress FROM portAddress
                    {
                        $$ = std::make_shared<nodes::compo::CDisconnection>(std::dynamic_pointer_cast<nodes::compo::CPortAddress>($2), std::dynamic_pointer_cast<nodes::compo::CPortAddress>($4));
                    }
                ;

/*-------------------------- grammar-literals-compo --------------------------*/

portAddress
                :   IDENTIFIER '@' componentIdent
                    {
                        $$ = std::make_shared<nodes::compo::CPortAddress>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1), $2);
                    }
                ;

componentIdent
                :   collectionPortLiteral
                    {
                        $$ = $1;
                    }
                |   '(' serviceInvocation ')'
                    {
                        $$ = $1;
                    }
                |   dereferenceLiteral
                    {
                        $$ = $1;
                    }
                |   IDENTIFIER
                    {
                        $$ = $1;
                    }
                ;

collectionPortLiteral
                :   IDENTIFIER '[' expression ']'
                    {
                        $$ = std::make_shared<nodes::compo::CCollectionPortLiteral>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1),
                                                                                    std::dynamic_pointer_cast<nodes::procedural::CAbstractExpression>($3));
                    }
                ;

serviceInvocation
                :   IDENTIFIER '.' serviceSign
                    {
                        $$ = std::make_shared<nodes::compo::CServiceInvocation>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1),
                                                                               std::dynamic_pointer_cast<nodes::compo::CServiceSignature>($3)->getNameSymbol(),
                                                                               $3);
                    }
                |   IDENTIFIER '.' IDENTIFIER '(' serviceInvocation ')'
                    {
                        $$ = std::make_shared<nodes::compo::CServiceInvocation>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($1),
                                                                               std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2),
                                                                               $4);
                    }
                ;

dereferenceLiteral
                :   '&' IDENTIFIER
                    {
                        $$ = std::make_shared<nodes::compo::CDereferenceLiteral>(std::dynamic_pointer_cast<nodes::procedural::CSymbol>($2));
                    }
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