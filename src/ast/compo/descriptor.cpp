#include "ast/compo/descriptor.h"

namespace ast {

	namespace compo {

		CDescriptor::CDescriptor( std::shared_ptr<ast::procedural::CSymbol> name,
		                          std::shared_ptr<ast::procedural::CSymbol> extends,
		                          const std::vector<std::shared_ptr<ast::CNode>>& body)
			: CNode(types::nodeType::DESCRIPTOR),
			  m_name(name),
			  m_extends(extends),
			  m_body(body),
			  m_defaultPort(std::make_shared<ast::compo::CSignaturesPort>(std::make_shared<ast::procedural::CSymbol>("default"),
			                false,
			                std::vector<std::shared_ptr<ast::compo::CServiceSignature>>(0))) {
		}

		void CDescriptor::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::string CDescriptor::getName() const {
			if (m_name) {
				return m_name->getStringValue();
			}
			return "";
		}

		std::string CDescriptor::getExtends() const {
			if (m_extends) {
				return m_extends->getStringValue();
			}
			return "";
		}

		size_t CDescriptor::getBodySize() const {
			return m_body.size();
		}

		std::shared_ptr<ast::CNode> CDescriptor::getBodyNodeAt(int index) const {
			std::shared_ptr<ast::CNode> node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		std::shared_ptr<ast::compo::CPort> CDescriptor::getDefaultPort() const {
			return m_defaultPort;
		}
	}

}