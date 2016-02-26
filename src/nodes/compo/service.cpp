#include "nodes/compo/service.h"

namespace nodes {

    namespace compo {
        
        CService::CService(   procedural::CSymbol* name,
                                        const std::vector<procedural::CSymbol*>& params,
                                        const std::vector<CNode*>& body,
                                        const std::vector<CNode*>& temporaries    )
        :   CNode(types::nodeType::SERVICE),
            CAbstractServConstr(name, params, body),
            m_temporaries(temporaries)
        {}

        CService::CService(const CService& other)
        : CNode(other),
          CAbstractServConstr(other)
        {
            *this = other;
        }

        CService::CService(CService&& other) noexcept
        : CNode(std::move(other)),
          CAbstractServConstr(std::move(other))
        {
            *this = std::move(other);
        }

        CService& CService::operator =(const CService& other) {
            if (&other != this) {
                for (CNode *node : other.m_temporaries) {
                    this->m_temporaries.push_back(node->clone());
                }
            }
            return *this;
        }

        CService& CService::operator =(CService&& other) noexcept {
            if (&other != this) {
                this->m_temporaries = std::move(other.m_temporaries);
            }
            return *this;
        }

        CNode * CService::clone() const {
            return new CService(*this);
        }

        CService::~CService() {
            for (CNode * node : m_temporaries) {
                delete node;
            }
        }

        size_t CService::getTemporariesSize() const {
            return m_temporaries.size();
        }

        CNode * CService::getTemporaryAt(int index) const {
            CNode * node = nullptr;
            try {
                node = m_temporaries.at(index);
            } catch (std::out_of_range ex) {
                // log error message
            }
            return node;
        }

        void CService::print(std::ostream& outStr) const {
            outStr << "\t";
            outStr << "service " << *m_name << " {" << std::endl;
            for (CNode *node : m_body) {
                outStr << "\t\t";
                outStr << *node;
            }
            outStr << "\t";
            outStr << "}" << std::endl;;
        }

    }
    
}