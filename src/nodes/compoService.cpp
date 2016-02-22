#include "compoService.h"

namespace compo {
    
    CCompoService::CCompoService(   CCompoSymbol* name,
                                    const std::vector<CCompoSymbol*>& params,
                                    const std::vector<CCompoNode*>& body,
                                    const std::vector<CCompoNode*>& temporaries    )
    :   CCompoNode(NodeTypeEnum::SERVICE),
        CCompoAbstractServConstr(name, params, body),
        m_temporaries(temporaries)
    {}
    
    CCompoService::CCompoService(const CCompoService& other)
    : CCompoNode(other),
      CCompoAbstractServConstr(other)
    {
        *this = other;
    }

    CCompoService::CCompoService(CCompoService&& other) noexcept
    : CCompoNode(std::move(other)),
      CCompoAbstractServConstr(std::move(other))
    {
        *this = std::move(other);
    }
    
    CCompoService& CCompoService::operator =(const CCompoService& other) {
        if (&other != this) {
            for (CCompoNode *node : other.m_temporaries) {
                this->m_temporaries.push_back(node->clone());
            }
        }
        return *this;
    }
    
    CCompoService& CCompoService::operator =(CCompoService&& other) noexcept {
        if (&other != this) {
            this->m_temporaries = std::move(other.m_temporaries);
        }
        return *this;
    }
    
    CCompoNode * CCompoService::clone() const {
        return new CCompoService(*this);
    }
    
    CCompoService::~CCompoService() {
        for (CCompoNode * node : m_temporaries) {
            delete node;
        }
    }

    size_t CCompoService::getTemporariesSize() const {
        return m_temporaries.size();
    }
    
    CCompoNode * CCompoService::getTemporaryAt(int index) const {
        CCompoNode * node = nullptr;
        try {
            node = m_temporaries.at(index);
        } catch (std::out_of_range ex) {
            // log error message
        }
        return node;
    }
    
    void CCompoService::print(std::ostream& outStr) const {
        outStr << "\t";
        outStr << "service " << m_name << "{" << std::endl;
        outStr << "}" << std::endl;;
    }

}