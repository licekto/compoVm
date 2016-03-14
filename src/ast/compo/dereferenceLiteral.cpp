#include "ast/compo/dereferenceLiteral.h"

namespace ast {

	namespace compo {

		CDereferenceLiteral::CDereferenceLiteral(std::shared_ptr<ast::procedural::CSymbol> parameter)
			:   CNode(types::nodeType::DEREFERENCE),
			    m_parameter(parameter) {
		}

		void CDereferenceLiteral::print(std::ostream& outstream) const {
			outstream << "&" << *m_parameter << std::endl;
		}

		std::shared_ptr<ast::procedural::CSymbol> CDereferenceLiteral::getParamName() const {
			return m_parameter;
		}
	}

}