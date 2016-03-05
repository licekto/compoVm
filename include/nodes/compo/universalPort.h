#pragma once

#include <memory>
#include "nodes/compo/port.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CUniversalPort
		 * \brief Class for universal port representation.
		 */
		class CUniversalPort : public CPort {
		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CUniversalPort(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			               bool atomicity = false,
			               bool collectivity = false);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
		};

	}

}