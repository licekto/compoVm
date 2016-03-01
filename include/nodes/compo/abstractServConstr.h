#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/symbol.h"
#include "nodes/procedural/compoundBody.h"

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
			std::shared_ptr<nodes::procedural::CSymbol> m_name; /**< Name */
			std::vector<std::shared_ptr<nodes::procedural::CSymbol>> m_params; /**< Vector of parameter names */
                        std::shared_ptr<nodes::procedural::CCompoundBody> m_body; /**< Compound body node */

			/**
			* Parametric constructor with default values
			* Constructor is made protected to prevent from creation of object of this (abstract) type.
			* @param name: Name of entity
			* @param params: Vector of parameter names
			* @param body: Vector of body expressions
			*/
			CAbstractServConstr(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
                                            const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params = std::vector<std::shared_ptr<nodes::procedural::CSymbol>>(0),
                                            std::shared_ptr<nodes::procedural::CCompoundBody> body = nullptr);

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
			std::string getName() const;

                        /**
			* Body size getter
                        * @return size of body vector
                        */
                        size_t getBodySize() const;
                        
                        /**
			* Adds new body node
			* @param node: shared pointer to node
			*/
			void addBodyNode(std::shared_ptr<nodes::CNode> node);
                        
			/**
			* Body getter
			* @return Constant pointer to vector with body expressions.
			*/
			std::shared_ptr<nodes::CNode> getBodyNodeAt(int index) const;
                        
                        /**
			* Temporaries size getter
                        * @return size of temporaries vector
                        */
                        size_t getTemporariesSize() const;
                        
                        /**
			* Adds new body node
			* @param node: shared pointer to node
			*/
                        void addTemporary(std::shared_ptr<nodes::procedural::CSymbol> temporary);
                        
                        /**
                         * Temporaries getter
                         * @param index: index of wanted temporary
                         * @return shared pointer to temporary symbol name
                         */
                        std::shared_ptr<nodes::procedural::CSymbol> getTemporaryAt (int index) const;

			/**
			 * Parameter size vector size
			 * @return number of parameters
			 */
			size_t getParamsSize() const;

			/**
			* Parameters setter
			* @param Constant pointer to pointer to parameter.
			*/
			void setParam(std::shared_ptr<nodes::procedural::CSymbol> param);
                        
			/**
			* Parameters getter
			* @return Constant pointer to vector with parameters.
			*/
			std::shared_ptr<nodes::procedural::CSymbol> getParamAt(int index) const;
		};

	}

}