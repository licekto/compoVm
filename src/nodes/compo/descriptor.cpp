#include "nodes/compo/descriptor.h"

namespace nodes {

	namespace compo {

		CDescriptor::CDescriptor( std::shared_ptr<nodes::procedural::CSymbol> name,
		                          std::shared_ptr<nodes::procedural::CSymbol> extends,
		                          const std::vector<std::shared_ptr<nodes::CNode>>& body)
			: CNode(types::nodeType::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body) {
		}

		void CDescriptor::print(std::ostream& outstream) const {
			outstream << "descriptor";
			if (m_name) {
				outstream << *m_name << " ";
			}
			if (m_extends) {
				outstream << "extends " << *m_extends;
			}
			outstream << " {" << std::endl;

			if (m_body.size() != 0) {
				for (std::shared_ptr<nodes::CNode> expr : m_body) {
					outstream << *expr;
				}
			}

			outstream << "}" << std::endl;
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

		std::shared_ptr<nodes::CNode> CDescriptor::getBodyNodeAt(int index) const {
			std::shared_ptr<nodes::CNode> node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

	}

}