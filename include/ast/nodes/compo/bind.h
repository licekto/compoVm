#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/compo/portAddress.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CBind
			 * \brief Class for abstract bindings representation
			 */
			class CBind : public virtual CNode {
			  protected:
				/**< Name symbol of port 1 */
				std::shared_ptr<compo::CPortAddress> m_portIdentification1;

				/**< Name symbol of port 2 */
				std::shared_ptr<compo::CPortAddress> m_portIdentification2;

				/**
				* Parametric constructor with default values
				* @param portIdentification1: address of source port
				* @param portIdentification2: address of destination port
				*/
				CBind(std::shared_ptr<compo::CPortAddress> portIdentification1 = nullptr,
				      std::shared_ptr<compo::CPortAddress> portIdentification2 = nullptr);

			  public:

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;

				/**
				 * Port name getter
				 * @return name symbol of port identification.
				 */
				std::shared_ptr<compo::CPortAddress> getSourcePortIdentification() const;

				/**
				* Port name getter
				                * @return name symbol of port identification.
				                */
				std::shared_ptr<compo::CPortAddress> getDestinationPortIdentification() const;
			};

		}

	}

}