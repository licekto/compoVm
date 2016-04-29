#pragma once

#include <memory>
#include <sstream>
#include <iostream>

#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/procedural/compoundBody.h"
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/procedural/stringLiteral.h"
#include "exceptions/runtime/serviceNotCompiledException.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CService
			 * \brief Class for Compo service representation
			 */
			class CService : public virtual CNode, public std::enable_shared_from_this<CService> {
			  protected:
				/**< Name */
				std::shared_ptr<compo::CServiceSignature> m_signature;

				/**< String representation of service code */
				std::shared_ptr<procedural::CStringLiteral> m_code;

				/**< Compound body node */
				std::shared_ptr<procedural::CCompoundBody> m_body;

				/**
				 * Checks if body is compiled
				 */
				void checkBodyCompiled() const;

			  public:
				/**
				* Parametric constructor with default values
				* @param signature: service signature
				* @param code: string representation of code
				*/
				CService(std::shared_ptr<compo::CServiceSignature> signature = nullptr,
				         std::shared_ptr<procedural::CStringLiteral> code = nullptr);

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
				 * Parsed AST node setter
				 * @param body
				 */
				void setParsedBodyNode(std::shared_ptr<procedural::CCompoundBody> body);

				/**
				* Body size getter
				                * @return size of body vector
				                */
				size_t getBodySize() const;

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

				/**
				 * Code string setter
				 * @param code
				 */
				void setBodyCode(const std::string& code);

				/**
				 * Code string getter
				 * @return code string
				 */
				std::string getBodyCode() const;

				/**
				 * Signature getter
				 * @return service signature
				 */
				std::shared_ptr<compo::CServiceSignature> getSignature() const;
			};

		}

	}

}