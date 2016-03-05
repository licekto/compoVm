#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/symbol.h"
#include "portAddress.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CBind : public virtual CNode {
		  protected:
			/**< Name symbol of port 1 */
			std::shared_ptr<nodes::compo::CPortAddress> m_portIdentification1;

                        /**< Name symbol of port 2 */
			std::shared_ptr<nodes::compo::CPortAddress> m_portIdentification2;
                        
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			* @param injectedWith: name of injected port
			*/
			CBind(std::shared_ptr<nodes::compo::CPortAddress> portIdentification1 = nullptr,
			      std::shared_ptr<nodes::compo::CPortAddress> portIdentification2 = nullptr);
                        
                    public:
			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			 * Port name getter
			 * @return name symbol of port identification.
			 */
			std::shared_ptr<nodes::compo::CPortAddress> getPortIdentification1() const;
                        
                        /**
			 * Port name getter
			 * @return name symbol of port identification.
			 */
			std::shared_ptr<nodes::compo::CPortAddress> getPortIdentification2() const;
                        
		};

	}

}