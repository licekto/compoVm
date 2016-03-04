#include "nodes/compo/dereferenceLiteral.h"

namespace nodes {

	namespace compo {

		CDereferenceLiteral::CDereferenceLiteral(std::shared_ptr<nodes::procedural::CSymbol> parameter)
			:   CNode(types::nodeType::DEREFERENCE),
			    m_parameter(parameter) {
		}

		void CDereferenceLiteral::print(std::ostream& outstream) const {
			outstream << "&" << *m_parameter << std::endl;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CDereferenceLiteral::getParamName() const {
			return m_parameter;
		}
	}

}