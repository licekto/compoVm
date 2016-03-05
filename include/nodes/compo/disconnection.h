#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/compo/bind.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CDisconnection : public CBind {
		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			*/
			CDisconnection(std::shared_ptr<nodes::compo::CPortAddress> portIdentification1 = nullptr,
			               std::shared_ptr<nodes::compo::CPortAddress> portIdentification2 = nullptr);

			/**
			* Virtual print function to call from operator <<
					* @param os: output stream
					* @see operator <<()
					*/
			virtual void print(std::ostream& os) const;
		};

	}

}