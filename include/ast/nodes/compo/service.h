#pragma once

#include <memory>
#include "ast/nodes/compo/abstractServConstr.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CService
			 * \brief Class for Compo service node representation.
			 */
			class CService : public CAbstractServConstr, public std::enable_shared_from_this<CService> {
			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name symbol of service
				* @param params: Vector of parameters
				* @param body: Vector of body nodes
				* @param temporaries: Vector of temporaries
				*/
				CService(std::shared_ptr<compo::CServiceSignature> signature = nullptr,
				         std::shared_ptr<procedural::CCompoundBody> body = nullptr);

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
			};

		}

	}

}