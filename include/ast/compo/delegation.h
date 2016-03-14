#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/compo/bind.h"

namespace ast {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CDelegation : public CBind {
		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			*/
			CDelegation(std::shared_ptr<ast::compo::CPortAddress> portIdentification1 = nullptr,
			            std::shared_ptr<ast::compo::CPortAddress> portIdentification2 = nullptr);

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);
		};

	}

}