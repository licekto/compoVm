#include "nodes/compo/serviceSignature.h"

namespace nodes {

	namespace compo {

		CServiceSignature::CServiceSignature(std::shared_ptr<nodes::procedural::CSymbol> name,
		                                     const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params)
			: CNode(types::nodeType::SERVICE_SIGN), m_name(name), m_params(params) {
		}

		void CServiceSignature::print(std::ostream& outstream) const {
			outstream << "\t";
		}

		std::string CServiceSignature::getName() const {
			if (m_name) {
				return m_name->getStringValue();
			}
			return "";
		}

		size_t CServiceSignature::getParamsSize() const {
			return m_params.size();
		}

		std::shared_ptr<nodes::procedural::CSymbol> CServiceSignature::getParamAt(int index) const {
			std::shared_ptr<nodes::procedural::CSymbol> param = nullptr;
			try {
				param = m_params.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return param;
		}

		void CServiceSignature::setParam(std::shared_ptr<nodes::procedural::CSymbol> param) {
			m_params.push_back(param);
		}

	}

}