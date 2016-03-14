#include "ast/compo/serviceSignature.h"

namespace ast {

	namespace compo {

		CServiceSignature::CServiceSignature(std::shared_ptr<ast::procedural::CSymbol> name,
		                                     const std::vector<std::shared_ptr<ast::CNode>>& params)
			: CNode(types::nodeType::SERVICE_SIGNATURE), m_name(name), m_params(params) {
		}

		void CServiceSignature::print(std::ostream& outstream) const {
			outstream << "\t";
		}

		std::shared_ptr<ast::procedural::CSymbol> CServiceSignature::getName() const {
			return m_name;
		}

		size_t CServiceSignature::getParamsSize() const {
			return m_params.size();
		}

		std::shared_ptr<ast::CNode> CServiceSignature::getParamAt(int index) const {
			std::shared_ptr<ast::CNode> param = nullptr;
			try {
				param = m_params.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return param;
		}

		void CServiceSignature::setParam(std::shared_ptr<ast::CNode> param) {
			m_params.push_back(param);
		}

		std::shared_ptr<ast::procedural::CSymbol> CServiceSignature::getNameSymbol() const {
			return m_name;
		}
	}

}