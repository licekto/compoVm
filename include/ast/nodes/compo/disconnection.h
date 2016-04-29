#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/compo/bind.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CDisconnection
			 * \brief Class for Compo disconnection representation
			 */
			class CDisconnection : public CBind, public std::enable_shared_from_this<CDisconnection> {
			  public:
				/**
				* Parametric constructor with default values
				* @param portIdentification1: address of source port
				* @param portIdentification2: address of destination port
				*/
				CDisconnection(std::shared_ptr<compo::CPortAddress> portIdentification1 = nullptr,
				               std::shared_ptr<compo::CPortAddress> portIdentification2 = nullptr);

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
			};

		}

	}

}