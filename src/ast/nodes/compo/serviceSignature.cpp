#include "ast/nodes/compo/serviceSignature.h"
#include "logger/logger.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CServiceSignature::CServiceSignature(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                                     const std::vector<std::shared_ptr<ast::nodes::CNode>>& params)
				: CNode(types::nodeType::SERVICE_SIGNATURE), m_name(name), m_params(params) {
			}

			void CServiceSignature::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			size_t CServiceSignature::getParamsSize() const {
				return m_params.size();
			}

			std::shared_ptr<ast::nodes::CNode> CServiceSignature::getParamAt(int index) const {
				std::shared_ptr<ast::nodes::CNode> param = nullptr;
				try {
					param = m_params.at(index);
				} catch (const std::out_of_range& ex) {
					TRACE(ERROR, ex.what());
				}
				return param;
			}

			void CServiceSignature::setParam(std::shared_ptr<ast::nodes::CNode> param) {
				m_params.push_back(param);
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CServiceSignature::getNameSymbol() const {
				return m_name;
			}
		}
	}
}