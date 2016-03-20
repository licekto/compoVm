#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/procedural/compoundBody.h"
#include "ast/nodes/compo/serviceSignature.h"

namespace ast {

    namespace nodes {
        
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
			std::shared_ptr<compo::CServiceSignature> m_signature;

			/**< Compound body node */
			std::shared_ptr<procedural::CCompoundBody> m_body;

			/**
			* Parametric constructor with default values
			* Constructor is made protected to prevent from creation of object of this (abstract) type.
			* @param name: name of entity
			* @param params: vector of parameter names
			* @param body: vector of body expressions
			*/
			CAbstractServConstr(std::shared_ptr<compo::CServiceSignature> signature = nullptr,
			                    std::shared_ptr<procedural::CCompoundBody> body = nullptr);

		  public:

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;

			/**
			* Name getter
			* @return Name of entity
			*/
			std::shared_ptr<procedural::CSymbol> getNameSymbol() const;

			/**
			* Body size getter
			                     * @return size of body vector
			                     */
			size_t getBodySize() const;

			/**
			* Adds new body node
					* @param node: shared pointer to node
					*/
			void addBodyNode(std::shared_ptr<CNode> node);

			/**
			* Body getter
			* @return Constant pointer to vector with body expressions.
			*/
			std::shared_ptr<CNode> getBodyNodeAt(int index) const;

			/**
			* Temporaries size getter
			                     * @return size of temporaries vector
			                     */
			size_t getTemporariesSize() const;

			/**
			* Adds new body node
					* @param node: shared pointer to node
					*/
			void addTemporary(std::shared_ptr<procedural::CSymbol> temporary);

			/**
			 * Temporaries getter
			 * @param index: index of wanted temporary
			 * @return shared pointer to temporary symbol name
			 */
			std::shared_ptr<procedural::CSymbol> getTemporaryAt (int index) const;

			/**
			 * Parameter size vector size
			 * @return number of parameters
			 */
			size_t getParamsSize() const;

			/**
			* Parameters setter
			* @param Constant pointer to pointer to parameter.
			*/
			void setParam(std::shared_ptr<procedural::CSymbol> param);

			/**
			* Parameters getter
			* @return Constant pointer to vector with parameters.
			*/
			std::shared_ptr<CNode> getParamAt(int index) const;
		};

	}
        
    }

}