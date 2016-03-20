#pragma once

#include <memory>
#include "ast/procedural/symbol.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CCompoundBody
		 * \brief Class for representation body of compound statement
		         *
		         * Compound statement contains temporaries (| var1 var2 | syntax) and standard procedural statements. Therefore separate class was made to simplify body handling.
		 */
		class CCompoundBody : public CAbstractStatement {
		  private:
			/**< Temporaries vector */
			std::vector<std::shared_ptr<ast::procedural::CSymbol>> m_temporaries;

			/**< Body nodes vector */
			std::vector<std::shared_ptr<ast::CNode>> m_body;

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			*/
			CCompoundBody(const std::vector<std::shared_ptr<ast::procedural::CSymbol>>& temporaries = std::vector<std::shared_ptr<ast::procedural::CSymbol>>(0),
			              const std::vector<std::shared_ptr<ast::CNode>>& body = std::vector<std::shared_ptr<ast::CNode>>(0));

			/**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			* Body size getter
                        * @return size of body vector
                        */
			size_t getBodySize() const;

			/**
			 * Body node setter
			 * @param node: shared pointer to node
			 */
			void addBodyNode(std::shared_ptr<ast::CNode> node);

			/**
			* Body getter
			* @return Constant pointer to body vector
			*/
			std::shared_ptr<ast::CNode> getBodyNodeAt(int index) const;

			/**
			* Temporaries size getter
                        * @return size of temporaries vector
                        */
			size_t getTemporariesSize() const;

			/**
			 * Temporary setter
			 * @param node: shared pointer to temporary
			 */
			void addTemporary(std::shared_ptr<ast::procedural::CSymbol> temporary);

			/**
			* Body getter
                        * @return Constant pointer to body vector
                        */
			std::shared_ptr<ast::procedural::CSymbol> getTemporaryAt(int index) const;
		};

	}

}