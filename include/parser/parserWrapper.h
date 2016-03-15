#pragma once

#include <memory>
#include <stack>

#include "parser/lexer.h"
#include "ast/node.h"
#include "ast/compo/port.h"
#include "ast/compo/bind.h"
#include "ast/compo/serviceSignature.h"
#include "ast/procedural/compoundBody.h"
#include "ast/procedural/symbol.h"
#include "ast/types/visibilityType.h"
#include "ast/types/portType.h"

/**
 * \class ParserWrapper
 * \brief Parser class for bison parser handling
 */
class ParserWrapper {
  private:
	/**< Lexer pointer */
	Lexer *m_lexer;

	/**< Vector of root nodes */
	std::shared_ptr<ast::CProgram> m_root;

	/**< Stack of nested blocks */
	std::stack<std::shared_ptr<ast::procedural::CCompoundBody>> m_blockStack;

	std::shared_ptr<ast::compo::CProvision> m_currentInteralProvision;

	std::shared_ptr<ast::compo::CProvision> m_currentExteralProvision;

	std::shared_ptr<ast::compo::CRequirement> m_currentInteralRequirement;

	std::shared_ptr<ast::compo::CRequirement> m_currentExteralRequirement;

	std::shared_ptr<ast::compo::CArchitecture> m_architecture;

	/**< Body of currently parsed descriptor */
	std::vector<std::shared_ptr<ast::compo::CService>> m_currentDescritporServices;

	std::vector<std::shared_ptr<ast::compo::CConstraint>> m_currentDescritporConstraints;

	/**< Parameters of currently parsed service */
	std::stack<std::vector<std::shared_ptr<ast::CNode>>> m_currentServiceParamsStack;

	/**< Visibility type of current requirement/provision */
	ast::types::visibilityType m_visibilityType;

	/**< Is current port atomic? */
	bool m_atomicity;

	/**< Currently parsed ports */
	std::vector<std::shared_ptr<ast::compo::CPort>> m_currentPorts;

	/**< Current body of compound statement */
	std::shared_ptr<ast::procedural::CCompoundBody> m_currentCompoundBody;

	/**< Current list of signatures (e.g. requirements, provisions) */
	std::vector<std::shared_ptr<ast::compo::CServiceSignature>> m_currentSignaturesList;

	/**< Name of currently parsed port */
	std::shared_ptr<ast::procedural::CSymbol> m_currentPortName;

	/**< Is current port collecting port? */
	bool m_collectivity;

	/**< Vector of current architecture body */
	std::vector<std::shared_ptr<ast::compo::CBind>> m_currentArchitectureBody;

  public:
	/**
	* Parametric constructor with default value
	* @param lexer: pointer to lexer
	*/
	ParserWrapper(Lexer *lexer = nullptr);

	/**
	* Destructor
	*/
	~ParserWrapper();

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
	Lexer * getLexer() const;

	/**
	* Root node setter
	* @param node pointer
	*/
	void addRootNode(std::shared_ptr<ast::CNode> node);

	/**
	* Root node getter
	* @param index: index of wanted node
	* @return root node at given index
	*/
	std::shared_ptr<ast::CProgram> getRootNode();

	/**
	 * Pushes new block context on the stack
	 * @param block: block smart pointer to push
	 */
	void pushBlock(std::shared_ptr<ast::procedural::CCompoundBody> block);

	/**
	 * Pops block from top of the stack
	 * @return smart pointer to block
	 *
	 * No "top" method implemented. Pop actually gets the top, removes data on the top and returns poped content.
	 */
	std::shared_ptr<ast::procedural::CCompoundBody> popBlock();

	/**
	 * Is stack empty?
	 * @return bool value
	 */
	bool isStackEmpty() const;

	void setInProvision(std::shared_ptr<ast::compo::CProvision> inProv);

	std::shared_ptr<ast::compo::CProvision> getInProvision();

	void setExProvision(std::shared_ptr<ast::compo::CProvision> exProv);

	std::shared_ptr<ast::compo::CProvision> getExProvision();

	void setInRequirement(std::shared_ptr<ast::compo::CRequirement> inReq);

	std::shared_ptr<ast::compo::CRequirement> getInRequirement();

	void setExRequirement(std::shared_ptr<ast::compo::CRequirement> exReq);

	std::shared_ptr<ast::compo::CRequirement> getExRequirement();

	void setArchitecture(std::shared_ptr<ast::compo::CArchitecture> arch);

	std::shared_ptr<ast::compo::CArchitecture> getArchitecture();

	/**
	 * Sets node of currently parsed descriptor
	 * @param node: smart pointer to body node
	 */
	void addDescriptorService(std::shared_ptr<ast::compo::CService> service);

	/**
	 * Returns vector of body nodes
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<ast::compo::CService>> * getDescriptorServices();

	/**
	 * Clears vector of body nodes
	 */
	void clearDescriptorServices();

	/**
	* Sets node of currently parsed descriptor
	 * @param node: smart pointer to body node
	 */
	void addDescriptorConstraint(std::shared_ptr<ast::compo::CConstraint> constraint);

	/**
	 * Returns vector of body nodes
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<ast::compo::CConstraint>> * getDescriptorConstraints();

	/**
	 * Clears vector of body nodes
	 */
	void clearDescriptorConstraints();

	/**
	 * Sets parameter of currently parsed service
	 * @param param: smart pointer to parameter name symbol
	 */
	void addServiceParam(std::shared_ptr<ast::CNode> param);

	/**
	 * Returns vector of service parameters
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<ast::CNode>> * getServiceParams();

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
	void setVisibility(ast::types::visibilityType type);

	/**
	 * Visibility getter
	 * @return visibilityType
	 */
	ast::types::visibilityType getVisibility() const;

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
	void addPort(std::shared_ptr<ast::compo::CPort> port);

	/**
	 * Returns vector of ports
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<ast::compo::CPort>> * getPorts();

	/**
	 * Clears vector of ports
	 */
	void clearPorts();

	/**
	 * Clears all vectors
	 */
	void clearAll();

	/**
	 * Current compound statement body setter
	 * @param body: shared pointer to CCompoundBody
	 */
	void setCurrentCompoundBody(std::shared_ptr<ast::procedural::CCompoundBody> body);

	/**
	 * Current compound statement body getter
	 * @return shared pointer to CCompoundBody
	 */
	std::shared_ptr<ast::procedural::CCompoundBody> getCurrentCompoundBody();

	/**
	* Adds currently parsed port
	 * @param port: smart pointer to port
	 */
	void addServiceSignature(std::shared_ptr<ast::compo::CServiceSignature> serviceSignature);

	/**
	 * Returns vector of ports
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<ast::compo::CServiceSignature>> * getServiceSignatures();

	/**
	 * Clears vector of ports
	 */
	void clearServiceSignatures();

	/**
	* Sets name of currently parsed port
	 * @param name
	 */
	void setPortName(std::shared_ptr<ast::procedural::CSymbol> name);

	/**
	 * Port name getter
	 * @return name
	 */
	std::shared_ptr<ast::procedural::CSymbol> getPortName() const;

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
	void addArchitectureNode(std::shared_ptr<ast::compo::CBind> bindNode);

	/**
	 * Returns vector of ports
	 * @return pointer to vector
	 */
	std::vector<std::shared_ptr<ast::compo::CBind>> * getArchitectureBody();

	/**
	 * Clears vector of architecture body nodes
	 */
	void clearArchitectureBody();
};
