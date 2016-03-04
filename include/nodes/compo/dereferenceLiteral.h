#pragma once

#include <memory>
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CNamedPort
		 * \brief Class for named port representation.
		 */
		class CDereferenceLiteral : public CNode {
		  protected:
			/**< Name parameter symbol of port */
			std::shared_ptr<nodes::procedural::CSymbol> m_parameter;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CDereferenceLiteral(std::shared_ptr<nodes::procedural::CSymbol> parameter = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			 * Signatures getter
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<nodes::procedural::CSymbol> getParamName() const;
		};

	}

}