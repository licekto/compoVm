#pragma once

#include <memory>
#include <stack>

#include "parser/lexer.h"
#include "nodes/node.h"
#include "nodes/compo/port.h"
#include "nodes/compo/serviceSignature.h"
#include "nodes/procedural/compoundBody.h"
#include "nodes/procedural/symbol.h"
#include "nodes/types/visibilityType.h"
#include "nodes/types/portType.h"

/**
 * \class ParserWrapper
 * \brief Parser class for bison parser handling
 */
class ParserWrapper {
  private:
	/**< Lexer pointer */
	Lexer *m_lexer;

	/**< Vector of root nodes */
	std::vector<std::shared_ptr<nodes::CNode>> m_rootNodes;

	/**< Stack of nested blocks */
	std::stack<std::shared_ptr<nodes::procedural::CCompoundBody>> m_blockStack;

	/**< Body of currently parsed descriptor */
	std::vector<std::shared_ptr<nodes::CNode>> m_currentDescritporBody;

	/**< Parameters of currently parsed service */
	std::vector<std::shared_ptr<nodes::procedural::CSymbol>> m_currentServiceParams;

	/**< Visibility type of current requirement/provision */
	nodes::types::visibilityType m_visibilityType;

	/**< Is current port atomic? */
	bool m_atomicity;

	/**< Currently parsed ports */
	std::vector<std::shared_ptr<nodes::compo::CPort>> m_currentPorts;

	/**< Current body of compound statement */
	std::shared_ptr<nodes::procedural::CCompoundBody> m_currentCompoundBody;

	/**< Current list of signatures (e.g. requirements, provisions) */
	std::vector<std::shared_ptr<nodes::compo::CServiceSignature>> m_currentSignaturesList;

	/**< Name of currently parsed port */
	std::shared_ptr<nodes::procedural::CSymbol> m_currentPortName;
        
        /**< Is current port collecting port? */
        bool m_collectivity;

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
	void setRootNode(std::shared_ptr<nodes::CNode> node);

	/**
	* Root node vector size getter
	* @return size of node vector
	*/
	size_t getRootNodesSize() const;

	/**
	* Root node getter
	* @param index: index of wanted node
	* @return root node at given index
	*/
	std::shared_ptr<nodes::CNode> getRootNodeAt(unsigned int index);

	/**
	 * Pushes new block context on the stack
	 * @param block: block smart pointer to push
	 */
	void pushBlock(std::shared_ptr<nodes::procedural::CCompoundBody> block);

	/**
	 * Pops block from top of the stack
	 * @return smart pointer to block
	 *
	 * No "top" method implemented. Pop actually gets the top, removes data on the top and returns poped content.
	 */
	std::shared_ptr<nodes::procedural::CCompoundBody> popBlock();

	/**
	 * Is stack empty?
	 * @return bool value
	 */
	bool isStackEmpty() const;

	/**
	 * Sets node of currently parsed descriptor
	 * @param node: smart pointer to body node
	 */
	void addDescriptorBodyNode(std::shared_ptr<nodes::CNode> node);

	/**
	 * Returns vector of body nodes
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<nodes::CNode>> * getDescriptorBody();

	/**
	 * Clears vector of body nodes
	 */
	void clearDescriptorBody();

	/**
	 * Sets parameter of currently parsed service
	 * @param param: smart pointer to parameter name symbol
	 */
	void addServiceParam(std::shared_ptr<nodes::procedural::CSymbol> param);

	/**
	 * Returns vector of service parameters
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<nodes::procedural::CSymbol>> * getServiceParams();

	/**
	 * Clears vector of service parameters
	 */
	void clearServiceParams();

	/**
	 * Sets visibility type of currently parsed provision/requirement
	 * @param type: visibility type
	 */
	void setVisibility(nodes::types::visibilityType type);

	/**
	 * Visibility getter
	 * @return visibilityType
	 */
	nodes::types::visibilityType getVisibility() const;

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
	void addPort(std::shared_ptr<nodes::compo::CPort> port);

	/**
	 * Returns vector of ports
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<nodes::compo::CPort>> * getPorts();

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
	void setCurrentCompoundBody(std::shared_ptr<nodes::procedural::CCompoundBody> body);

	/**
	 * Current compound statement body getter
	 * @return shared pointer to CCompoundBody
	 */
	std::shared_ptr<nodes::procedural::CCompoundBody> getCurrentCompoundBody();

	/**
	* Adds currently parsed port
	 * @param port: smart pointer to port
	 */
	void addServiceSignature(std::shared_ptr<nodes::compo::CServiceSignature> serviceSignature);

	/**
	 * Returns vector of ports
	 * @return reference to vector
	 */
	std::vector<std::shared_ptr<nodes::compo::CServiceSignature>> * getServiceSignatures();

	/**
	 * Clears vector of ports
	 */
	void clearServiceSignatures();

	/**
	* Sets name of currently parsed port
	 * @param name
	 */
	void setPortName(std::shared_ptr<nodes::procedural::CSymbol> name);

	/**
	 * Port name getter
	 * @return name
	 */
	std::shared_ptr<nodes::procedural::CSymbol> getPortName() const;
        
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
};
