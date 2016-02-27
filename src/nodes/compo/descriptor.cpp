#include "nodes/compo/descriptor.h"

namespace nodes {

	namespace compo {

		CDescriptor::CDescriptor( procedural::CSymbol *name,
		                          procedural::CSymbol *extends,
		                          const std::vector<CNode*>& body)
			: CNode(types::nodeType::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body) {
		}

		CDescriptor::CDescriptor(const CDescriptor& other)
			: CNode(other),
			  m_name(new procedural::CSymbol(*other.m_name)),
			  m_extends(new procedural::CSymbol(*other.m_extends)) {
			*this = other;
		}

		CDescriptor::CDescriptor(CDescriptor&& other) noexcept
			: CNode(std::move(other)),
			  m_name(other.m_name),
			  m_extends(other.m_extends),
			  m_body(std::move(other.m_body)) {
			other.m_name = nullptr;
			other.m_extends = nullptr;
		}

		CDescriptor& CDescriptor::operator =(const CDescriptor& other) {
			if (&other != this) {
				m_nodeType = other.m_nodeType;
				m_name = new procedural::CSymbol(*other.m_name);
				m_extends = new procedural::CSymbol(*other.m_extends);
				for (CNode *node : other.m_body) {
					this->m_body.push_back(node->clone());
				}
			}
			return *this;
		}

		CDescriptor& CDescriptor::operator =(CDescriptor&& other) noexcept {
			if (&other != this) {
				m_nodeType = std::move(other.m_nodeType);
				m_name = other.m_name;
				other.m_name = nullptr;
				m_extends = other.m_extends;
				other.m_extends = nullptr;
				m_body = std::move(other.m_body);
			}
			return *this;
		}

		CNode * CDescriptor::clone() const {
			return new CDescriptor(*this);
		}

		CDescriptor::~CDescriptor() {
			delete m_name;
			delete m_extends;
			for (CNode *expr : m_body) {
				delete expr;
			}
		}

		void CDescriptor::print(std::ostream& outstream) const {
			outstream << typeName(m_nodeType) << " ";
			if (m_name) {
				outstream << *m_name << " ";
			}
			if (m_extends) {
				outstream << "extends " << *m_extends;
			}
			outstream << " {" << std::endl;

			if (m_body.size() != 0) {
				for (CNode *expr : m_body) {
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

		void CDescriptor::setExtends(procedural::CSymbol* extends) {
			m_extends = extends;
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

		CNode * CDescriptor::getBodyNodeAt(int index) const {
			CNode * node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

	}

}