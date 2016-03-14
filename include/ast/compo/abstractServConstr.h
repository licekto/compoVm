#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/symbol.h"
#include "ast/procedural/compoundBody.h"
#include "ast/compo/serviceSignature.h"

namespace ast {

	namespace compo {

		/**
		 * \class CAbstractServConstr
		 * \brief Abstract base class for service and constraint nodes.
		 *
		 * Abstract base class for service and constraint nodes. Class inherits virtually from CCompoNode prevent diamond problem.
		 * This class was designed because of the similar structure of service a constraint nodes thus to prevent code repetition.
		 */
		class CAbstractServConstr : public virtual CNode {
		  protected:
			/**< Name */
			std::shared_ptr<ast::compo::CServiceSignature> m_signature;

			/**< Compound body node */
			std::shared_ptr<ast::procedural::CCompoundBody> m_body;

			/**
			* Parametric constructor with default values
			* Constructor is made protected to prevent from creation of object of this (abstract) type.
			* @param name: name of entity
			* @param params: vector of parameter names
			* @param body: vector of body expressions
			*/
			CAbstractServConstr(std::shared_ptr<ast::compo::CServiceSignature> signature = nullptr,
			                    std::shared_ptr<ast::procedural::CCompoundBody> body = nullptr);

		  public:
			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			* Name getter
			* @return Name of entity
			*/
			std::shared_ptr<ast::procedural::CSymbol> getNameSymbol() const;

			/**
			* Body size getter
			                     * @return size of body vector
			                     */
			size_t getBodySize() const;

			/**
			* Adds new body node
					* @param node: shared pointer to node
					*/
			void addBodyNode(std::shared_ptr<ast::CNode> node);

			/**
			* Body getter
			* @return Constant pointer to vector with body expressions.
			*/
			std::shared_ptr<ast::CNode> getBodyNodeAt(int index) const;

			/**
			* Temporaries size getter
			                     * @return size of temporaries vector
			                     */
			size_t getTemporariesSize() const;

			/**
			* Adds new body node
					* @param node: shared pointer to node
					*/
			void addTemporary(std::shared_ptr<ast::procedural::CSymbol> temporary);

			/**
			 * Temporaries getter
			 * @param index: index of wanted temporary
			 * @return shared pointer to temporary symbol name
			 */
			std::shared_ptr<ast::procedural::CSymbol> getTemporaryAt (int index) const;

			/**
			 * Parameter size vector size
			 * @return number of parameters
			 */
			size_t getParamsSize() const;

			/**
			* Parameters setter
			* @param Constant pointer to pointer to parameter.
			*/
			void setParam(std::shared_ptr<ast::procedural::CSymbol> param);

			/**
			* Parameters getter
			* @return Constant pointer to vector with parameters.
			*/
			std::shared_ptr<ast::CNode> getParamAt(int index) const;
		};

	}

}