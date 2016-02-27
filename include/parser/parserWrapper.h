#pragma once

#include <memory>

#include "parser/lexer.h"
#include "nodes/node.h"

/**
 * \class ParserWrapper
 * \brief Parser class for bison parser handling
 */
class ParserWrapper {
  private:
	Lexer                         * m_lexer;            /**< Lexer pointer */
	std::vector<std::shared_ptr<nodes::CNode>> m_rootNodes;        /**< Vector of root nodes */

  public:
	/**
	* Parametric constructor with default value
	* @param lexer: pointer to lexer
	*/
	ParserWrapper               (Lexer *lexer = nullptr);

	/**
	* Destructor
	*/
	~ParserWrapper              ();

	/**
	* Launch parsing
	* @param is: input stream
	*/
	int                                     parse                       (std::istream& is);

	/**
	* Parse whole input
	* @param is: input stream
	*/
	void                                    parseAll                    (std::istream& is);

	/**
	* Clears root nodes vector
	*/
	void                                    clear                       ();

	/**
	* Handle errors
	*/
	void                                    error                       (const std::string& message);

	/**
	* Lexer getter
	* @return Lexer pointer
	*/
	Lexer *                                 getLexer                    () const;

	/**
	* Root node setter
	* @param node pointer
	*/
	void                                    setRootNode                 (std::shared_ptr<nodes::CNode> node);

	/**
	* Root node vector size getter
	* @return size of node vector
	*/
	size_t                                  getRootNodesSize            () const;

	/**
	* Root node getter
	* @param index: index of wanted node
	* @return root node at given index
	*/
	std::shared_ptr<nodes::CNode>                     getRootNodeAt               (unsigned int index);
};
