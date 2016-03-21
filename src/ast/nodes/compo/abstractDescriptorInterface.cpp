#include "ast/nodes/compo/abstractDescriptorInterface.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CAbstractDescriptorInterface::CAbstractDescriptorInterface(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			        std::shared_ptr<ast::nodes::procedural::CSymbol> extends)
				: CNode(types::nodeType::DESCRIPTOR),
				  m_name(name),
				  m_extends(extends) {
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CAbstractDescriptorInterface::getNameSymbol() const {
				return m_name;
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CAbstractDescriptorInterface::getExtendsSymbol() const {
				return m_extends;
			}

		}

	}

}