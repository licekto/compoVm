#include "nodes/compo/provision.h"

namespace nodes {

    namespace compo {
    
        CProvision::CProvision(   types::visibilityType type,
                                            const std::vector<CPort*>& ports)
        :   CNode(types::nodeTypeEnum::PROVISION),
            CAbstractReqProv(type, ports)
        {}

        CProvision::CProvision(const CProvision& other)
        : CNode(other),
          CAbstractReqProv(other)
        {}


        CProvision::CProvision(CProvision&& other) noexcept
        : CNode(std::move(other)),
          CAbstractReqProv(std::move(other))
        {}

        CProvision& CProvision::operator =(const CProvision& other) {
            if (&other != this) {
                *this = other;
            }
            return *this;
        }

        CNode * CProvision::clone() const {
            return new CProvision(*this);
        }

        CProvision& CProvision::operator =(CProvision&& other) noexcept {
            if (&other != this) {
                *this = std::move(other);
            }
            return *this;
        }

        CProvision::~CProvision() {
        }

    }
    
}