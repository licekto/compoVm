#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/compo/bind.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CConnection : public CBind, public std::enable_shared_from_this<CConnection> {
		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			*/
			CConnection(std::shared_ptr<compo::CPortAddress> portIdentification1 = nullptr,
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