#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CPortAddress : public CNode {
		  private:
			/**< Name symbol of port */
			std::shared_ptr<nodes::procedural::CSymbol> m_portName;

			/**< Component node */
			std::shared_ptr<nodes::CNode> m_component;

		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			* @param injectedWith: name of injected port
			*/
			CPortAddress(std::shared_ptr<nodes::procedural::CSymbol> portName = nullptr,
			             std::shared_ptr<nodes::CNode> component = nullptr);

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
			std::shared_ptr<nodes::procedural::CSymbol> getPortName() const;

			/**
			* Component node getter
					 * @return shared pointer to CNode
					 */
			std::shared_ptr<nodes::CNode> getComponent() const;
		};

	}

}