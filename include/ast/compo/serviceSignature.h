#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/symbol.h"

namespace ast {

	namespace compo {

		/**
		 * \class CServiceSignature
		 * \brief Class for Compo service signature representation.
		 */
		class CServiceSignature : public CNode {
		  private:
			/**< Name */
			std::shared_ptr<ast::procedural::CSymbol> m_name;

			/**< Vector of parameter names */
			std::vector<std::shared_ptr<ast::CNode>> m_params;
		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name symbol of service
			* @param params: Vector of parameters
			*/
			CServiceSignature(std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
			                  const std::vector<std::shared_ptr<ast::CNode>>& params = std::vector<std::shared_ptr<ast::CNode>>(0));

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
			std::shared_ptr<ast::procedural::CSymbol> getName() const;

			/**
			* Name symbol getter
			            * @return shared_ptr to CSymbol
			            */
			std::shared_ptr<ast::procedural::CSymbol> getNameSymbol() const;

			/**
			* Parameter size vector size
			            * @return number of parameters
			            */
			size_t getParamsSize() const;

			/**
			* Parameters setter
			* @param Constant pointer to pointer to parameter.
			*/
			void setParam(std::shared_ptr<ast::CNode> param);

			/**
			* Parameters getter
			* @return Constant pointer to vector with parameters.
			*/
			std::shared_ptr<ast::CNode> getParamAt(int index) const;
		};

	}

}