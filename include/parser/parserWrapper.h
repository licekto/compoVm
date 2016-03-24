#pragma once

#include <memory>
#include <stack>
#include <algorithm>

#include "definitions/allDefinitions.h"

#include "parser/lexer.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/semantic/redefinedDescriptorException.h"
#include "exceptions/semantic/redefinedInterfaceException.h"
#include "exceptions/semantic/redefinedPortException.h"


/**
 * \class ParserWrapper
 * \brief Parser class for bison parser handling
 */
class ParserWrapper {
  private:
	/**< Lexer pointer */
	ptr(Lexer) m_lexer;

	ptr(ast::semantic::CGlobalDescriptorTable) m_descriptorTable;

	/**< Vector of root nodes */
	ptr(ast_program) m_root;

	/**< Stack of nested blocks */
	std::stack<ptr(ast_compound)> m_blockStack;

	ptr(ast_provision) m_currentInteralProvision;

	ptr(ast_provision) m_currentExteralProvision;

	ptr(ast_requirement) m_currentInteralRequirement;

	ptr(ast_requirement) m_currentExteralRequirement;

	ptr(ast_architecture) m_architecture;

	/**< Body of currently parsed descriptor */
	std::vector<ptr(ast_service)> m_currentDescritporServices;

	std::vector<ptr(ast_constraint)> m_currentDescritporConstraints;

	/**< Parameters of currently parsed service */
	std::stack<std::vector<ptr(ast_node)>> m_currentServiceParamsStack;

	/**< Visibility type of current requirement/provision */
	ast::nodes::types::visibilityType m_visibilityType;

	/**< Is current port atomic? */
	bool m_atomicity;

	/**< Currently parsed ports */
	std::vector<ptr(ast_port)> m_currentPorts;

	/**< Current body of compound statement */
	ptr(ast_compound) m_currentCompoundBody;

	/**< Current list of signatures (e.g. requirements, provisions) */
	std::vector<ptr(ast_servicesignature)> m_currentSignaturesList;

	/**< Name of currently parsed port */
	ptr(ast_symbol) m_currentPortName;

	/**< Is current port collecting port? */
	bool m_collectivity;

	/**< Vector of current architecture body */
	std::vector<ptr(ast_bind)> m_currentArchitectureBody;

	ptr(ast_compound) m_serviceBody;

  public:
	/**
	* Parametric constructor with default value
	* @param lexer: pointer to lexer
	*/
	ParserWrapper(ptr(Lexer) lexer = nullptr, ptr(ast::semantic::CGlobalDescriptorTable) descriptorTable = nullptr);

	/**
	* Destructor
	*/
	~ParserWrapper();

        int parse(std::string code);
        
	/**
	* Launch parsing
	* @param is: input stream
	*/
	int parse(std::istream& is);

	/**
	* Parse whole input
	* @param is: input stream
	*/
	void parseAll(std::istream& is);

	/**
	* Clears root nodes vector
	*/
	void clearRootNodes();

	/**
	* Handle errors
	*/
	void error(const std::string& message);

	/**
	* Lexer getter
	* @return Lexer pointer
	*/
	ptr(Lexer) getLexer() const;

	void addSymbolToDescriptorTable(ptr(ast_descriptorinterface) node);

	ptr(ast::semantic::CGlobalDescriptorTable) getDescriptorTable();

	void clearDescriptorTable();

	/**
	* Root node setter
	* @param node pointer
	*/
	void addRootNode(ptr(ast_node) node);

	/**
	* Root node getter
	* @param index: index of wanted node
	* @return root node at given index
	*/
	ptr(ast_program) getRootNode();

	/**
	 * Pushes new block context on the stack
	 * @param block: block smart pointer to push
	 */
	void pushBlock(ptr(ast_compound) block);

	/**
	 * Pops block from top of the stack
	 * @return smart pointer to block
	 *
	 * No "top" method implemented. Pop actually gets the top, removes data on the top and returns poped content.
	 */
	ptr(ast_compound) popBlock();

	/**
	 * Is stack empty?
	 * @return bool value
	 */
	bool isStackEmpty() const;

	void setInProvision(ptr(ast_provision) inProv);

	ptr(ast_provision) getInProvision();

	void setExProvision(ptr(ast_provision) exProv);

	ptr(ast_provision) getExProvision();

	void setInRequirement(ptr(ast_requirement) inReq);

	ptr(ast_requirement) getInRequirement();

	void setExRequirement(ptr(ast_requirement) exReq);

	ptr(ast_requirement) getExRequirement();

	void setArchitecture(ptr(ast_architecture) arch);

	ptr(ast_architecture) getArchitecture();

	/**
	 * Sets node of currently parsed descriptor
	 * @param node: smart pointer to body node
	 */
	void addDescriptorService(ptr(ast_service) service);

	/**
	 * Returns vector of body nodes
	 * @return reference to vector
	 */
	std::vector<ptr(ast_service)> * getDescriptorServices();

	/**
	 * Clears vector of body nodes
	 */
	void clearDescriptorServices();

	/**
	* Sets node of currently parsed descriptor
	 * @param node: smart pointer to body node
	 */
	void addDescriptorConstraint(ptr(ast_constraint) constraint);

	/**
	 * Returns vector of body nodes
	 * @return reference to vector
	 */
	std::vector<ptr(ast_constraint)> * getDescriptorConstraints();

	/**
	 * Clears vector of body nodes
	 */
	void clearDescriptorConstraints();

	/**
	 * Sets parameter of currently parsed service
	 * @param param: smart pointer to parameter name symbol
	 */
	void addServiceParam(ptr(ast_node) param);

	/**
	 * Returns vector of service parameters
	 * @return reference to vector
	 */
	std::vector<ptr(ast_node)> * getServiceParams();

	/**
	 * Push service parameters vector on the stack
	 */
	void pushServiceParams();

	/**
	 * Pop service parameters vector from the stack
	 */
	void popServiceParams();

	/**
	 * Sets visibility type of currently parsed provision/requirement
	 * @param type: visibility type
	 */
	void setVisibility(ast::nodes::types::visibilityType type);

	/**
	 * Visibility getter
	 * @return visibilityType
	 */
	ast::nodes::types::visibilityType getVisibility() const;

	/**
	 * Sets atomicity of currently parsed port
	 * @param atomicity
	 */
	void setAtomicity(bool atomicity);

	/**
	 * Atomicity getter
	 * @return bool value
	 */
	bool getAtomicity() const;

	/**
	 * Adds currently parsed port
	 * @param port: smart pointer to port
	 */
	void addPort(ptr(ast_port) port);

	/**
	 * Returns vector of ports
	 * @return reference to vector
	 */
	std::vector<ptr(ast_port)> * getPorts();

	/**
	 * Clears vector of ports
	 */
	void clearPorts();

	/**
	 * Clears all vectors
	 */
	void clearContext();

	void clearAll();

	/**
	 * Current compound statement body setter
	 * @param body: shared pointer to CCompoundBody
	 */
	void setCurrentCompoundBody(ptr(ast_compound) body);

	/**
	 * Current compound statement body getter
	 * @return shared pointer to CCompoundBody
	 */
	ptr(ast_compound) getCurrentCompoundBody();

	/**
	* Adds currently parsed port
	 * @param port: smart pointer to port
	 */
	void addServiceSignature(ptr(ast_servicesignature) serviceSignature);

	/**
	 * Returns vector of ports
	 * @return reference to vector
	 */
	std::vector<ptr(ast_servicesignature)> * getServiceSignatures();

	/**
	 * Clears vector of ports
	 */
	void clearServiceSignatures();

	/**
	* Sets name of currently parsed port
	 * @param name
	 */
	void setPortName(ptr(ast_symbol) name);

	/**
	 * Port name getter
	 * @return name
	 */
	ptr(ast_symbol) getPortName() const;

	/**
	* Sets collectivity of currently parsed port
	 * @param atomicity
	 */
	void setCollectivity(bool collectivity);

	/**
	 * Collectivity getter
	 * @return bool value
	 */
	bool getCollectivity() const;

	/**
	* Adds currently parsed bind node
	 * @param port: smart pointer to bind node
	 */
	void addArchitectureNode(ptr(ast_bind) bindNode);

	/**
	 * Returns vector of ports
	 * @return pointer to vector
	 */
	std::vector<ptr(ast_bind)> * getArchitectureBody();

	/**
	 * Clears vector of architecture body nodes
	 */
	void clearArchitectureBody();

	void addServiceBody(ptr(ast_compound) body);

	void parseServices();
};
