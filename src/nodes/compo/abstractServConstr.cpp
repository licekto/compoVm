#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		CAbstractServConstr::CAbstractServConstr(   std::shared_ptr<nodes::procedural::CSymbol> name,
		        const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params,
		        const std::vector<std::shared_ptr<nodes::CNode>>& body)
			: CNode(types::nodeType::SERVICE), m_name(name), m_params(params), m_body(body) {
		}

		void CAbstractServConstr::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << typeName(m_nodeType) << " ";

			if (m_name) {
				outstream << *m_name << " (";
			}

			bool first = true;
			for (std::shared_ptr<nodes::procedural::CSymbol> symbol : m_params) {
				if (!first) {
					outstream << ", ";
					first = false;
				}
				outstream << *symbol;
			}

			outstream << ") {" << std::endl;
			outstream << "\t";
			outstream << "}" << std::endl;
		}

		std::string CAbstractServConstr::getName() const {
			if (m_name) {
				return m_name->getStringValue();
			}
			return "";
		}

		size_t CAbstractServConstr::getBodySize() const {
			return m_body.size();
		}

		std::shared_ptr<nodes::CNode> CAbstractServConstr::getBodyNodeAt(int index) const {
			std::shared_ptr<nodes::CNode> node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		void CAbstractServConstr::setBodyNode(std::shared_ptr<nodes::CNode> bodyNode) {
			m_body.push_back(bodyNode);
		}

		size_t CAbstractServConstr::getParamsSize() const {
			return m_params.size();
		}

		std::shared_ptr<nodes::procedural::CSymbol> CAbstractServConstr::getParamAt(int index) const {
			std::shared_ptr<nodes::procedural::CSymbol> param = nullptr;
			try {
				param = m_params.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return param;
		}

		void CAbstractServConstr::setParam(std::shared_ptr<nodes::procedural::CSymbol> param) {
			m_params.push_back(param);
		}

	}

}