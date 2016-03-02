#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		CAbstractServConstr::CAbstractServConstr(std::shared_ptr<nodes::procedural::CSymbol> name,
                                                         const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params,
                                                         std::shared_ptr<nodes::procedural::CCompoundBody> body)
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
                    if (m_body) {
                        return m_body->getBodySize();
                    }
                    return 0;
                }
                
                size_t CAbstractServConstr::getTemporariesSize() const {
                    if (m_body) {
                        return m_body->getTemporariesSize();
                    }
                    return 0;
                }
                
		std::shared_ptr<nodes::CNode> CAbstractServConstr::getBodyNodeAt(int index) const {
                    if (m_body) {
                        return m_body->getBodyNodeAt(index);
                    }
                    return nullptr;
		}

		void CAbstractServConstr::addBodyNode(std::shared_ptr<nodes::CNode> node) {
                    if (m_body) {
			m_body->addBodyNode(node);
                    }
		}

                void CAbstractServConstr::addTemporary(std::shared_ptr<nodes::procedural::CSymbol> temporary) {
                    if (m_body) {
                        m_body->addTemporary(temporary);
                    }
                }
                
                std::shared_ptr<nodes::procedural::CSymbol> CAbstractServConstr::getTemporaryAt(int index) const {
                    if (m_body) {
                        return m_body->getTemporaryAt(index);
                    }
                    return nullptr;
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