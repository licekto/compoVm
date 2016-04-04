#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CServiceSignature
			 * \brief Class for Compo service signature representation.
			 */
			class CServiceSignature : public CNode, public std::enable_shared_from_this<CServiceSignature> {
			  private:
				/**< Name */
				std::shared_ptr<procedural::CSymbol> m_name;

				/**< Vector of parameter names */
				std::vector<std::shared_ptr<CNode>> m_params;
			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name symbol of service
				* @param params: Vector of parameters
				*/
				CServiceSignature(std::shared_ptr<procedural::CSymbol> name = nullptr,
				                  const std::vector<std::shared_ptr<CNode>>& params = std::vector<std::shared_ptr<CNode>>(0));

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				* Name symbol getter
				                * @return shared_ptr to CSymbol
				                */
				std::shared_ptr<procedural::CSymbol> getNameSymbol() const;

				/**
				* Parameter size vector size
				                * @return number of parameters
				                */
				size_t getParamsSize() const;

				/**
				* Parameters setter
				* @param Constant pointer to pointer to parameter.
				*/
				void setParam(std::shared_ptr<CNode> param);

				/**
				* Parameters getter
				* @return Constant pointer to vector with parameters.
				*/
				std::shared_ptr<CNode> getParamAt(int index) const;
			};

		}

	}

}