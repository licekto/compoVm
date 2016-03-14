#pragma once

#include <memory>
#include "ast/compo/abstractServConstr.h"

namespace ast {

	namespace compo {

		/**
		 * \class CService
		 * \brief Class for Compo service node representation.
		 */
		class CService : public CAbstractServConstr {
		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name symbol of service
			* @param params: Vector of parameters
			* @param body: Vector of body nodes
			* @param temporaries: Vector of temporaries
			*/
			CService(std::shared_ptr<ast::compo::CServiceSignature> signature = nullptr,
			         std::shared_ptr<ast::procedural::CCompoundBody> body = nullptr);

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);
		};

	}

}