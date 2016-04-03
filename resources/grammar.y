%{
#include <iostream>
#include <memory>

#include "parser/parserWrapper.h"
#include "parser/lexer.h"

#include "definitions/allDefinitions.h"

#define yylex()                  parser->getLexer()->yylex()
#define yyerror(parser, message) parser->error(message)
%}

%define api.value.type {std::shared_ptr<ast::nodes::CNode>}
%define parse.error verbose
%define parse.lac full

%debug

%parse-param {ParserWrapper *parser}

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

literal
                :   CONSTANT
                    {
                        $$ = $1;
                    }
                |   STRING_LITERAL
                    {
                        $$ = $1;
                    }

primary_expression
                :   IDENTIFIER
                    {
                        $$ = $1;
                    }
                |   literal
                    {
                        $$ = $1;
                    }
                |   '(' expression ')'
                    {
                        $$ = new_ptr(ast_parens)($2);
                    }
                |   service_invocation
                    {
                        $$ = $1;
                    }
                ;

multiplicative_expression
                :   primary_expression
                    {
                        $$ = $1;
                    }
                |   multiplicative_expression '*' primary_expression
                    {
                        $$ = new_ptr(ast_multiplication)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                |   multiplicative_expression '/' primary_expression
                    {
                        $$ = new_ptr(ast_division)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                ;

additive_expression
                :   multiplicative_expression
                    {
                        $$ = $1;
                    }
                |   additive_expression '+' multiplicative_expression
                    {
                        $$ = new_ptr(ast_addition)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                |   additive_expression '-' multiplicative_expression
                    {
                        $$ = new_ptr(ast_subtraction)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                ;

relational_expression
                :   additive_expression
                    {
                        $$ = $1;
                    }
                |   relational_expression '<' additive_expression
                    {
                        $$ = new_ptr(ast_less)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                |   relational_expression '>' additive_expression
                    {
                        $$ = new_ptr(ast_greater)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                |   relational_expression LE_OP additive_expression
                    {
                        $$ = new_ptr(ast_lessorequal)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                |   relational_expression GE_OP additive_expression
                    {
                        $$ = new_ptr(ast_greaterorequal)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                ;

equality_expression
                :   relational_expression
                    {
                        $$ = $1;
                    }
                |   equality_expression EQ_OP additive_expression
                    {
                        $$ = new_ptr(ast_equality)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                |   equality_expression NE_OP additive_expression
                    {
                        $$ = new_ptr(ast_nonequality)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                ;

logical_and_expression
                :   equality_expression
                    {
                        $$ = $1;
                    }
                |   logical_and_expression AND_OP equality_expression
                    {
                        $$ = new_ptr(ast_and)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                ;

logical_or_expression
                :   logical_and_expression
                    {
                        $$ = $1;
                    }
                |   logical_or_expression OR_OP logical_and_expression
                    {
                        $$ = new_ptr(ast_or)(cast(ast_expression)($1), cast(ast_expression)($3));
                    }
                ;


assignment_expression
                :   logical_or_expression
                    {
                        $$ = $1;
                    }
                |   IDENTIFIER ASSIGNMENT expression
                    {
                        $$ = new_ptr(ast_assignment)(cast(ast_symbol)($1), $3);
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
                |   disconnections
                    {
                        $$ = $1;
                    }
                |   connections
                    {
                        $$ = $1;
                    }
                |   delegations
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
                        $$ = parser->getCurrentCompoundBody();
                        parser->setCurrentCompoundBody(parser->popBlock());
                    }
                ;

push_context
                :   {
                        parser->pushBlock(parser->getCurrentCompoundBody());
                        parser->setCurrentCompoundBody(new_ptr(ast_compound)());
                    }
                ;

temporaries
                :   '|' temporaries_list '|'
                |   empty
                ;

temporaries_list
                :   IDENTIFIER
                    {
                        parser->getCurrentCompoundBody()->addTemporary(cast(ast_symbol)($1));
                    }
                |   temporaries_list IDENTIFIER
                    {
                        parser->getCurrentCompoundBody()->addTemporary(cast(ast_symbol)($2));
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
                        $$ = new_ptr(ast_if)(cast(ast_expression)($3),
                                             cast(ast_compound)($5),
                                             nullptr);
                    }
                |   IF '(' expression ')' statement ELSE statement
                    {
                        $$ = new_ptr(ast_if)(cast(ast_expression)($3),
                                             cast(ast_compound)($5),
                                             cast(ast_compound)($7));
                    }
                ;

iteration_statement
                :   WHILE '(' expression ')' statement
                    {
                        $$ = new_ptr(ast_while)(cast(ast_expression)($3), cast(ast_compound)($5));
                    }
                |   FOR '(' assignment_expression ';' expression_statement expression ')' statement
                    {
                        $$ = new_ptr(ast_for)(cast(ast_assignment)($3),
                                                   cast(ast_expression)($5),
                                                   cast(ast_expression)($6),
                                                   cast(ast_compound)($8));
                    }
                ;

jump_statement
                :   CONTINUE ';'
                    {
                        $$ = new_ptr(ast_continue)();
                    }
                |   BREAK ';'
                    {
                        $$ = new_ptr(ast_break)();
                    }
                |   RETURN expression ';'
                    {
                        $$ = new_ptr(ast_return)(cast(ast_expression)($2));
                    }
                ;

/*---------------------------- grammar-compo ---------------------------------*/

start           
                :   descriptor_interface END
                    {
                         YYACCEPT; return 0;
                    }
                |   service_body END
                    {
                         YYACCEPT; return 0;
                    }
                ;

service_body
                :   compound_statement
                    {
                         parser->addServiceBody(cast(ast_compound)$1);
                    }

descriptor_interface
                :   descriptor_interface descriptor
                    {
                        parser->addRootNode($2);
                    }
                |   descriptor_interface interface
                    {
                        parser->addRootNode($2);
                    }
                |   empty
                ;

descriptor      
                :   DESCRIPTOR IDENTIFIER inheritance '{' compo_expressions '}'
                    {
                        ptr(ast_descriptor) descriptor = new_ptr(ast_descriptor)(cast(ast_symbol)($2),
                                                                                 cast(ast_symbol)($3),
                                                                                 parser->getArchitecture(),
                                                                                *parser->getPorts(),
                                                                                *parser->getDescriptorServices(),
                                                                                *parser->getDescriptorConstraints());
                        parser->addSymbolToDescriptorTable(descriptor);
                        $$ = descriptor;
                        parser->clearContext();
                    }
                ;

interface       
                :   INTERFACE IDENTIFIER inheritance service_signatures_list
                    {
                        ptr(ast_interface) interface = new_ptr(ast_interface)(cast(ast_symbol)($2),
                                                                              cast(ast_symbol)($3),
                                                                             *parser->getServiceSignatures());
                        parser->addSymbolToDescriptorTable(interface);
                        $$ = interface;
                        parser->clearContext();
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
                :   provision_requirement
		|   constraint
		|   service
		|   architecture
                ;

provision_requirement
                :   visibility role provision_requirement_signature
                ;

visibility
                :   EXTERNALLY
                    {
                        parser->setVisibility(types::visibilityType::EXTERNAL);
                    }
                |   INTERNALLY
                    {
                        parser->setVisibility(types::visibilityType::INTERNAL);
                    }
                |   empty
                    {
                        parser->setVisibility(types::visibilityType::EXTERNAL);
                    }
                ;

role
                :   PROVIDES
		    {
                        parser->setRole(ast_roletype::PROVIDES);
		    }
                |   REQUIRES
                    {
                        parser->setRole(ast_roletype::REQUIRES);
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
                        cast(ast_port)($5)->setKindOf(cast(ast_symbol)($6));
			parser->addPort(cast(ast_port)($5));
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
                        parser->setPortName(cast(ast_symbol)($1));
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
                        $$ = new_ptr(ast_namedport)(parser->getPortName(),
                                                    parser->getAtomicity(),
                                                    parser->getCollectivity(),
                                                    parser->getVisibility(),
                                                    parser->getRole(),
                                                    cast(ast_symbol)($1));
                    }
                |   '*'
                    {
                        $$ = new_ptr(ast_universalport)(parser->getPortName(),
                                                        parser->getAtomicity(),
                                                        parser->getCollectivity(),
                                                        parser->getVisibility(),
                                                        parser->getRole());
                    }
                |   service_signatures_list
                    {
                        $$ = new_ptr(ast_signaturesport)(parser->getPortName(),
                                                         parser->getAtomicity(),
                                                         parser->getCollectivity(),
                                                         parser->getVisibility(),
                                                         parser->getRole(),
                                                        *parser->getServiceSignatures());
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
                :   SERVICE service_signature service_code
                    {
                        parser->addDescriptorService(new_ptr(ast_service)(cast(ast_servicesignature)($2), cast(ast_string)($3)));
                    }
                ;

service_code
                :   { parser->getLexer()->setServiceState(); } STRING_LITERAL
                    {
                        $$ = $2;
                    }
                ;

service_signature
                :   IDENTIFIER '(' service_params ')'
                    {
                        $$ = new_ptr(ast_servicesignature)(cast(ast_symbol)($1), *parser->getServiceParams());
                        parser->popServiceParams();
                    }
                ;

service_signature_call
                :   IDENTIFIER '(' push_parameters service_runtime_params ')'
                    {
                        $$ = new_ptr(ast_servicesignature)(cast(ast_symbol)($1), *parser->getServiceParams());
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
                        parser->addServiceSignature(cast(ast_servicesignature)($1));
                    }
                |   service_signature ';' service_signatures
                    {
                        parser->addServiceSignature(cast(ast_servicesignature)($1));
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
                :   primary_expression
                    {
                        parser->addServiceParam($1);
                    }

                ;

constraint	
                :   CONSTRAINT service_signature compound_statement
                    {
                        parser->addDescriptorConstraint(new_ptr(ast_constraint)(cast(ast_servicesignature)($2), cast(ast_compound)($3)));
                    }
		;

architecture	
                :   ARCHITECTURE '{' bindings '}'
                    {
                        parser->setArchitecture(new_ptr(ast_architecture)(*parser->getArchitectureBody()));
                        parser->clearArchitectureBody();
                    }
		;

bindings
                :   disconnections
                |   connections
                |   delegations
                |   empty
                ;

connections     
                :   connection ';' bindings
                    {
                        parser->addArchitectureNode(cast(ast_bind)($1));
                    }
                ;

connection      
                :   CONNECT port_address TO port_address
                    {
                        $$ = new_ptr(ast_connection)(cast(ast_portaddress)($2), cast(ast_portaddress)($4));
                    }
                ;

disconnections  
                :   disconnection ';' bindings
                    {
                        parser->addArchitectureNode(cast(ast_bind)($1));
                    }
                ;

disconnection   
                :   DISCONNECT port_address FROM port_address
                    {
                        $$ = new_ptr(ast_disconnection)(cast(ast_portaddress)($2), cast(ast_portaddress)($4));
                    }
                ;

delegations  
                :   delegation ';' bindings
                    {
                        parser->addArchitectureNode(cast(ast_bind)($1));
                    }
                ;

delegation   
                :   DELEGATE port_address TO port_address
                    {
                        $$ = new_ptr(ast_delegation)(cast(ast_portaddress)($2), cast(ast_portaddress)($4));
                    }
                ;

/*-------------------------- grammar-literals-compo --------------------------*/

port_address
                :   IDENTIFIER '@' component_identifier
                    {
                        $$ = new_ptr(ast_portaddress)(cast(ast_symbol)($1), $3);
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
                        $$ = new_ptr(ast_collectionportliteral)(cast(ast_symbol)($1), cast(ast_expression)($3));
                    }
                ;

service_invocation
                :   IDENTIFIER '.' service_signature_call
                    {
                        $$ = new_ptr(ast_serviceinvocation)(cast(ast_symbol)($1),
                                                            cast(ast_servicesignature)($3)->getNameSymbol(),
                                                            $3);
                    }
                ;

dereference_literal
                :   '&' IDENTIFIER
                    {
                        $$ = new_ptr(ast_dereference)(cast(ast_symbol)($2));
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

    parse(is);

    parseServices();
}