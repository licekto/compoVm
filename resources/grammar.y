%{
#include <iostream>
#include <memory>

#include "parser/parserWrapper.h"
#include "parser/lexer.h"
#include "ast/node.h"
#include "ast/types/visibilityType.h"
#include "ast/types/portType.h"
#include "ast/compo/architecture.h"
#include "ast/compo/service.h"
#include "ast/compo/dereferenceLiteral.h"
#include "ast/compo/collectionPortLiteral.h"
#include "ast/compo/constraint.h"
#include "ast/compo/connection.h"
#include "ast/compo/disconnection.h"
#include "ast/compo/delegation.h"
#include "ast/compo/port.h"
#include "ast/compo/portAddress.h"
#include "ast/compo/namedPort.h"
#include "ast/compo/signaturesPort.h"
#include "ast/compo/universalPort.h"
#include "ast/compo/descriptor.h"
#include "ast/compo/provision.h"
#include "ast/compo/requirement.h"
#include "ast/compo/interface.h"
#include "ast/compo/serviceSignature.h"
#include "ast/compo/serviceInvocation.h"
#include "ast/compo/bind.h"
#include "ast/procedural/symbol.h"
#include "ast/procedural/ifStatement.h"
#include "ast/procedural/forStatement.h"
#include "ast/procedural/whileStatement.h"
#include "ast/procedural/breakStatement.h"
#include "ast/procedural/continueStatement.h"
#include "ast/procedural/returnStatement.h"
#include "ast/procedural/abstractExpression.h"
#include "ast/procedural/assignmentExpression.h"
#include "ast/procedural/additionExpression.h"
#include "ast/procedural/subtractionExpression.h"
#include "ast/procedural/multiplicationExpression.h"
#include "ast/procedural/divisionExpression.h"
#include "ast/procedural/equalityExpression.h"
#include "ast/procedural/nonEqualityExpression.h"
#include "ast/procedural/logicalAndExpression.h"
#include "ast/procedural/logicalOrExpression.h"
#include "ast/procedural/lessExpression.h"
#include "ast/procedural/lessOrEqualExpression.h"
#include "ast/procedural/greaterExpression.h"
#include "ast/procedural/greaterOrEqualExpression.h"

#include "ast/procedural/constant.h"
#include "ast/procedural/parens.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)
%}

%define api.value.type {std::shared_ptr<ast::CNode>}
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
                        $$ = std::make_shared<ast::procedural::CParens>($2);
                    }
                ;

multiplicative_expression
                :   primary_expression
                    {
                        $$ = $1;
                    }
                |   multiplicative_expression '*' primary_expression
                    {
                        $$ = std::make_shared<ast::procedural::CMultiplicationExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                |   multiplicative_expression '/' primary_expression
                    {
                        $$ = std::make_shared<ast::procedural::CDivisionExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;

additive_expression
                :   multiplicative_expression
                    {
                        $$ = $1;
                    }
                |   additive_expression '+' multiplicative_expression
                    {
                        $$ = std::make_shared<ast::procedural::CAdditionExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                |   additive_expression '-' multiplicative_expression
                    {
                        $$ = std::make_shared<ast::procedural::CSubtractionExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;

relational_expression
                :   additive_expression
                    {
                        $$ = $1;
                    }
                |   relational_expression '<' additive_expression
                    {
                        $$ = std::make_shared<ast::procedural::CLessExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                |   relational_expression '>' additive_expression
                    {
                        $$ = std::make_shared<ast::procedural::CGreaterExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                |   relational_expression LE_OP additive_expression
                    {
                        $$ = std::make_shared<ast::procedural::CLessOrEqualExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                |   relational_expression GE_OP additive_expression
                    {
                        $$ = std::make_shared<ast::procedural::CGreaterOrEqualExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;

equality_expression
                :   relational_expression
                    {
                        $$ = $1;
                    }
                |   equality_expression EQ_OP additive_expression
                    {
                        $$ = std::make_shared<ast::procedural::CEqualityExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                |   equality_expression NE_OP additive_expression
                    {
                        $$ = std::make_shared<ast::procedural::CNonEqualityExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;

logical_and_expression
                :   equality_expression
                    {
                        $$ = $1;
                    }
                |   logical_and_expression AND_OP equality_expression
                    {
                        $$ = std::make_shared<ast::procedural::CLogicalAndExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;

logical_or_expression
                :   logical_and_expression
                    {
                        $$ = $1;
                    }
                |   logical_or_expression OR_OP logical_and_expression
                    {
                        $$ = std::make_shared<ast::procedural::CLogicalOrExpression>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($1), std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;


assignment_expression
                :   logical_or_expression
                    {
                        $$ = $1;
                    }
                |   primary_expression ASSIGNMENT expression
                    {
                        $$ = std::make_shared<ast::procedural::CAssignmentExpression>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1), $3);
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
                |   push_context '{' '}'
                    {
                        $$ = nullptr;
                    }
                ;

push_context
                :   {
                        parser->pushBlock(parser->getCurrentCompoundBody());
                        parser->setCurrentCompoundBody(std::make_shared<ast::procedural::CCompoundBody>());
                    }
                ;

temporaries
                :   '|' temporaries_list '|'
                |   empty
                ;

temporaries_list
                :   IDENTIFIER
                    {
                        parser->getCurrentCompoundBody()->addTemporary(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1));
                    }
                |   temporaries_list IDENTIFIER
                    {
                        parser->getCurrentCompoundBody()->addTemporary(std::dynamic_pointer_cast<ast::procedural::CSymbol>($2));
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
                        $$ = std::make_shared<ast::procedural::CIfStatement>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3),
                                                                               std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($5),
                                                                               nullptr);
                    }
                |   IF '(' expression ')' statement ELSE statement
                    {
                        $$ = std::make_shared<ast::procedural::CIfStatement>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3),
                                                                               std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($5),
                                                                               std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($7));
                    }
                ;

iteration_statement
                :   WHILE '(' expression ')' statement
                    {
                        $$ = std::make_shared<ast::procedural::CWhileStatement>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3),
                                                                                  std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($5));
                    }
                |   FOR '(' assignment_expression ';' expression_statement expression ')' statement
                    {
                        $$ = std::make_shared<ast::procedural::CForStatement>(std::dynamic_pointer_cast<ast::procedural::CAssignmentExpression>($3),
                                                                                std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($5),
                                                                                std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($6),
                                                                                std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($8));
                    }
                ;

jump_statement
                :   CONTINUE ';'
                    {
                        $$ = std::make_shared<ast::procedural::CContinueStatement>();
                    }
                |   BREAK ';'
                    {
                        $$ = std::make_shared<ast::procedural::CBreakStatement>();
                    }
                |   RETURN expression ';'
                    {
                        $$ = std::make_shared<ast::procedural::CReturnStatement>(std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($2));
                    }
                ;

/*---------------------------- grammar-compo ---------------------------------*/

start           
                :   descriptor_interface END
                    {
                         YYACCEPT; return 0;
                    }
                ;

descriptor_interface
                :   descriptor descriptor_interface
                    {
                        parser->addRootNode($1);
                    }
                |   interface descriptor_interface
                    {
                        parser->addRootNode($1);
                    }
                |   empty
                ;

descriptor      
                :   DESCRIPTOR IDENTIFIER inheritance '{' compo_expressions '}'
                    {
                        $$ = std::make_shared<ast::compo::CDescriptor>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($2),
                                                                         std::dynamic_pointer_cast<ast::procedural::CSymbol>($3),
                                                                         parser->getInProvision(),
                                                                         parser->getExProvision(),
                                                                         parser->getInRequirement(),
                                                                         parser->getExRequirement(),
                                                                         parser->getArchitecture(),
                                                                         *parser->getDescriptorServices(),
                                                                         *parser->getDescriptorConstraints());
                        parser->clearAll();
                    }
                ;

interface       
                :   INTERFACE IDENTIFIER inheritance service_signatures_list
                    {
                        $$ = std::make_shared<ast::compo::CInterface>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($2),
                                                                        std::dynamic_pointer_cast<ast::procedural::CSymbol>($3),
                                                                        *parser->getServiceSignatures());
                    }
                ;

inheritance     
                :   EXTENDS IDENTIFIER
                    {
                        $$ = $2;
                    }
                |   empty
                    {
                        $$ = nullptr;
                    }
                ;

compo_expressions      
                :   compo_expression compo_expressions
                |   empty           // Empty descriptor allowed
                ;


compo_expression	
                :   provision
		|   requirement
		|   constraint
		|   service
		|   architecture
                ;

provision     
                :   visibility PROVIDES provision_requirement_signature
		    {
                        if (parser->getVisibility() == ast::types::visibilityType::EXTERNAL)
                        {
                            parser->setExProvision(std::make_shared<ast::compo::CProvision>(parser->getVisibility(), *parser->getPorts()));
                        }
                        else
                        {
                            parser->setInProvision(std::make_shared<ast::compo::CProvision>(parser->getVisibility(), *parser->getPorts()));
                        }
                        parser->clearPorts();
		    }
                ;

requirement   
                :   visibility REQUIRES provision_requirement_signature
                    {
                        if (parser->getVisibility() == ast::types::visibilityType::EXTERNAL)
                        {
                            parser->setExRequirement(std::make_shared<ast::compo::CRequirement>(parser->getVisibility(), *parser->getPorts()));
                        }
                        else
                        {
                            parser->setInRequirement(std::make_shared<ast::compo::CRequirement>(parser->getVisibility(), *parser->getPorts()));
                        }
                        parser->clearPorts();
		    }
                ;

visibility
                :   EXTERNALLY
                    {
                        parser->setVisibility(ast::types::visibilityType::EXTERNAL);
                    }
                |   INTERNALLY
                    {
                        parser->setVisibility(ast::types::visibilityType::INTERNAL);
                    }
                |   empty
                    {
                        parser->setVisibility(ast::types::visibilityType::EXTERNAL);
                    }
                ;

provision_requirement_signature     
                :   '{' ports '}'
                ;

ports
                :   port ';'
                |   port ';' ports
		;

port
                :   atomic port_name collecting ':' port_signature of_kind
		    {
                        std::dynamic_pointer_cast<ast::compo::CPort>($5)->setKindOf(std::dynamic_pointer_cast<ast::procedural::CSymbol>($6));
			parser->addPort(std::dynamic_pointer_cast<ast::compo::CPort>($5));
		    }
		;

atomic
                :   ATOMIC
                    {
                        parser->setAtomicity(true);
                    }
		|   empty
                    {
                        parser->setAtomicity(false);
                    }
		;

port_name
                :   IDENTIFIER
                    {
                        parser->setPortName(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1));
                    }
                ;

collecting        
                :   '[' ']'
                    {
                        parser->setCollectivity(true);
                    }
                |   empty
                    {
                        parser->setCollectivity(false);
                    }
                ;

port_signature        
                :   IDENTIFIER
                    {
                        $$ = std::make_shared<ast::compo::CNamedPort>(parser->getPortName(),
                                                                        parser->getAtomicity(),
                                                                        std::dynamic_pointer_cast<ast::procedural::CSymbol>($1),
                                                                        parser->getCollectivity());
                    }
                |   '*'
                    {
                        $$ = std::make_shared<ast::compo::CUniversalPort>(parser->getPortName(),
                                                                            parser->getAtomicity(),
                                                                            parser->getCollectivity());
                    }
                |   service_signatures_list
                    {
                        $$ = std::make_shared<ast::compo::CSignaturesPort>(parser->getPortName(),
                                                                             parser->getAtomicity(),
                                                                            *parser->getServiceSignatures(),
                                                                             parser->getCollectivity());
                        parser->clearServiceSignatures();
                    }
                ;

of_kind          
                :   OFKIND IDENTIFIER
                    {
                        $$ = $2;
                    }
                |   empty
                    {
                        $$ = nullptr;
                    }
                ;

service         
                :   SERVICE service_signature compound_statement
                    {
                        parser->addDescriptorService(std::make_shared<ast::compo::CService>(std::dynamic_pointer_cast<ast::compo::CServiceSignature>($2),
                                                                                               std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($3)));
                    }
                ;

service_signature
                :   IDENTIFIER '(' service_params ')'
                    {
                        $$ = std::make_shared<ast::compo::CServiceSignature>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1), *parser->getServiceParams());
                        parser->popServiceParams();
                    }
                ;

service_signature_call
                :   IDENTIFIER '(' push_parameters service_runtime_params ')'
                    {
                        $$ = std::make_shared<ast::compo::CServiceSignature>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1), *parser->getServiceParams());
                        parser->popServiceParams();
                    }
                ;

push_parameters
                :   {
                        parser->pushServiceParams();
                    }
                ;

service_signatures    
                :   service_signature
                    {
                        parser->addServiceSignature(std::dynamic_pointer_cast<ast::compo::CServiceSignature>($1));
                    }
                |   service_signature ';' service_signatures
                    {
                        parser->addServiceSignature(std::dynamic_pointer_cast<ast::compo::CServiceSignature>($1));
                    }
                |   empty
                ;

service_signatures_list
                :   '{' service_signatures '}'

service_params   
                :   parameter
                |   parameter ',' service_params
                |   empty
                ;

parameter
                :   IDENTIFIER
                    {
                        parser->addServiceParam($1);
                    }
                ;

service_runtime_params
                :   parameter_runtime
                |   parameter_runtime ',' service_runtime_params
                |   empty
                ;

parameter_runtime   
                :   service_invocation
                    {
                        parser->addServiceParam($1);
                    }
                |   primary_expression
                    {
                        parser->addServiceParam($1);
                    }

                ;

constraint	
                :   CONSTRAINT service_signature compound_statement
                    {
                        parser->addDescriptorConstraint(std::make_shared<ast::compo::CConstraint>(std::dynamic_pointer_cast<ast::compo::CServiceSignature>($2),
                                                                                                  std::dynamic_pointer_cast<ast::procedural::CCompoundBody>($3)));
                    }
		;

architecture	
                :   ARCHITECTURE '{' bindings '}'
                    {
                        parser->setArchitecture(std::make_shared<ast::compo::CArchitecture>(*parser->getArchitectureBody()));
                        parser->clearArchitectureBody();
                    }
		;

bindings
                :   disconnections
                |   connections
                |   delegations
                ;

connections     
                :   connection ';' bindings
                    {
                        parser->addArchitectureNode(std::dynamic_pointer_cast<ast::compo::CBind>($1));
                    }
                |   empty
                ;

connection      
                :   CONNECT port_address TO port_address
                    {
                        $$ = std::make_shared<ast::compo::CConnection>(std::dynamic_pointer_cast<ast::compo::CPortAddress>($2), std::dynamic_pointer_cast<ast::compo::CPortAddress>($4));
                    }
                ;

disconnections  
                :   disconnection ';' bindings
                    {
                        parser->addArchitectureNode(std::dynamic_pointer_cast<ast::compo::CBind>($1));
                    }
                ;

disconnection   
                :   DISCONNECT port_address FROM port_address
                    {
                        $$ = std::make_shared<ast::compo::CDisconnection>(std::dynamic_pointer_cast<ast::compo::CPortAddress>($2), std::dynamic_pointer_cast<ast::compo::CPortAddress>($4));
                    }
                ;

delegations  
                :   delegation ';' bindings
                    {
                        parser->addArchitectureNode(std::dynamic_pointer_cast<ast::compo::CBind>($1));
                    }
                ;

delegation   
                :   DELEGATE port_address TO port_address
                    {
                        $$ = std::make_shared<ast::compo::CDelegation>(std::dynamic_pointer_cast<ast::compo::CPortAddress>($2), std::dynamic_pointer_cast<ast::compo::CPortAddress>($4));
                    }
                ;

/*-------------------------- grammar-literals-compo --------------------------*/

port_address
                :   IDENTIFIER '@' component_identifier
                    {
                        $$ = std::make_shared<ast::compo::CPortAddress>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1), $3);
                    }
                ;

component_identifier
                :   collection_port_literal
                    {
                        $$ = $1;
                    }
                |   '(' service_invocation ')'
                    {
                        $$ = $2;
                    }
                |   dereference_literal
                    {
                        $$ = $1;
                    }
                |   IDENTIFIER
                    {
                        $$ = $1;
                    }
                ;

collection_port_literal
                :   IDENTIFIER '[' expression ']'
                    {
                        $$ = std::make_shared<ast::compo::CCollectionPortLiteral>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1),
                                                                                    std::dynamic_pointer_cast<ast::procedural::CAbstractExpression>($3));
                    }
                ;

service_invocation
                :   IDENTIFIER '.' service_signature_call
                    {
                        $$ = std::make_shared<ast::compo::CServiceInvocation>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($1),
                                                                                std::dynamic_pointer_cast<ast::compo::CServiceSignature>($3)->getNameSymbol(),
                                                                                $3);
                    }
                ;

dereference_literal
                :   '&' IDENTIFIER
                    {
                        $$ = std::make_shared<ast::compo::CDereferenceLiteral>(std::dynamic_pointer_cast<ast::procedural::CSymbol>($2));
                    }
                ;
empty
                :
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