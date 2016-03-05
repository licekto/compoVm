#pragma once

#include <memory>
#include "nodes/compo/port.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CNamedPort
		 * \brief Class for named port representation.
		 */
		class CNamedPort : public CPort {
		  protected:
			/**< Name parameter symbol of port */
			std::shared_ptr<nodes::procedural::CSymbol> m_nameParam;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CNamedPort(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			           bool atomicity = false,
			           std::shared_ptr<nodes::procedural::CSymbol> nameParam = nullptr,
			           bool collectivity = false);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			 * Signatures getter
			 * @param index
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<nodes::procedural::CSymbol> getParamName() const;
		};

	}

}