#include "ast/compo/abstractDescriptorInterface.h"

namespace ast {

	namespace compo {

		CAbstractDescriptorInterface::CAbstractDescriptorInterface(std::shared_ptr<ast::procedural::CSymbol> name,
		                         std::shared_ptr<ast::procedural::CSymbol> extends)
			: CNode(types::nodeType::DESCRIPTOR),
			  m_name(name),
			  m_extends(extends) {
		}

		std::shared_ptr<ast::procedural::CSymbol> CAbstractDescriptorInterface::getNameSymbol() const {
			return m_name;
		}

		std::shared_ptr<ast::procedural::CSymbol> CAbstractDescriptorInterface::getExtendsSymbol() const {
			return m_extends;
		}
                
	}

}