#pragma once

#include <memory>
#include "ast/nodes/compo/service.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CConstraint
			 * \brief Class for Compo constraint representation.
			 */
			class CConstraint : public CNode, public std::enable_shared_from_this<CConstraint> {
                        private:
                                /**< Name */
				std::shared_ptr<compo::CServiceSignature> m_signature;
                                
				/**< Compound body node */
				std::shared_ptr<procedural::CCompoundBody> m_body;
                            
			  public:
				/**
				* Parametric constructor with default values
				* @param name: Name of constraint
				* @param params: Vector of parameters
				* @param body: Vector of body expressions
				*/
				CConstraint(std::shared_ptr<compo::CServiceSignature> signature = nullptr,
				            std::shared_ptr<procedural::CCompoundBody> body = nullptr);

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
                                
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