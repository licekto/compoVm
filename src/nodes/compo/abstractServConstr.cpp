#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		CAbstractServConstr::CAbstractServConstr(   procedural::CSymbol* name,
		        const std::vector<procedural::CSymbol*>& params,
		        const std::vector<CNode*>& body)
			: CNode(types::nodeType::SERVICE), m_name(name), m_params(params), m_body(body) {
		}

		CAbstractServConstr::CAbstractServConstr(const CAbstractServConstr& other)
			: CNode(other) {
			*this = other;
		}

		CAbstractServConstr::CAbstractServConstr(CAbstractServConstr&& other) noexcept
			: CNode(std::move(other)),
			  m_name(other.m_name),
			  m_params(std::move(other.m_params)),
			  m_body(std::move(other.m_body)) {
			other.m_name = nullptr;
		}

		CAbstractServConstr& CAbstractServConstr::operator =(const CAbstractServConstr& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;

				this->m_name = new procedural::CSymbol(*other.m_name);

				for (procedural::CSymbol *symbol : other.m_params) {
					this->m_params.push_back(new procedural::CSymbol(*symbol));
				}

				for (CNode *node : other.m_body) {
					this->m_body.push_back(node->clone());
				}
			}

			return *this;
		}

		CAbstractServConstr& CAbstractServConstr::operator =(CAbstractServConstr&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_name = other.m_name;
				other.m_name = nullptr;
				this->m_params = std::move(other.m_params);
				this->m_body = std::move(other.m_body);
			}
			return *this;
		}

		CNode * CAbstractServConstr::clone() const {
			return new CAbstractServConstr(*this);
		}

		CAbstractServConstr::~CAbstractServConstr() {
			delete m_name;

			for (procedural::CSymbol *symbol : m_params) {
				delete symbol;
			}

			for (CNode *expr : m_body) {
				delete expr;
			}
		}

		void CAbstractServConstr::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << typeName(m_nodeType) << " ";

			if (m_name) {
				outstream << *m_name << " (";
			}

			bool first = true;
			for (procedural::CSymbol *symbol : m_params) {
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

		CNode * CAbstractServConstr::getBodyNodeAt(int index) const {
			CNode * node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		void CAbstractServConstr::setBodyNode(CNode* bodyNode) {
			m_body.push_back(bodyNode);
		}

		size_t CAbstractServConstr::getParamsSize() const {
			return m_params.size();
		}

		procedural::CSymbol * CAbstractServConstr::getParamAt(int index) const {
			procedural::CSymbol * param = nullptr;
			try {
				param = m_params.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return param;
		}

		void CAbstractServConstr::setParam(procedural::CSymbol* param) {
			m_params.push_back(param);
		}

	}

}