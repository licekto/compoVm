#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/compo/serviceSignature.h"
#include "ast/procedural/symbol.h"

namespace ast {

	namespace compo {

		/**
		 * \class CSignaturesPort
		 * \brief Class for port with signatures list.
		 */
		class CInterface : public CNode {
		  private:
			/**< Name of interface */
			std::shared_ptr<ast::procedural::CSymbol> m_name;

			/**< Name of base interface */
			std::shared_ptr<ast::procedural::CSymbol> m_extends;

			/**< List of signatures */
			std::vector<std::shared_ptr<ast::compo::CServiceSignature>> m_signaturesList;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CInterface(std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
			           std::shared_ptr<ast::procedural::CSymbol> extends = nullptr,
			           std::vector<std::shared_ptr<ast::compo::CServiceSignature>> list = std::vector<std::shared_ptr<ast::compo::CServiceSignature>>(0));

			/**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);

			/**
			* Interface name getter
					 * @return name symbol.
					 */
			std::shared_ptr<ast::procedural::CSymbol> getName() const;

			/**
			* Base interface name getter
					 * @return name symbol.
					 */
			std::shared_ptr<ast::procedural::CSymbol> getExtends() const;

			/**
			 * Signatures size getter
			 * @return size_t
			 */
			size_t getSignaturesSize() const;

			/**
			 * Signatures getter
			 * @param index
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<ast::compo::CServiceSignature> getSignatureAt(unsigned int index) const;
		};

	}

}