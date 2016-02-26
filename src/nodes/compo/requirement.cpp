#include "nodes/compo/requirement.h"

namespace nodes {

    namespace compo {
    
        CRequirement::CRequirement(   types::visibilityType type,
                                                const std::vector<CPort*>& ports)
        :   CNode(types::NodeTypeEnum::REQUIREMENT),
            CAbstractReqProv(type, ports)
        {}

        CRequirement::CRequirement(const CRequirement& other)
        : CNode(other),
          CAbstractReqProv(other)
        {}


        CRequirement::CRequirement(CRequirement&& other) noexcept
        : CNode(std::move(other)),
          CAbstractReqProv(std::move(other))
        {}

        CRequirement& CRequirement::operator =(const CRequirement& other) {
            if (&other != this) {
                *this = other;
            }
            return *this;
        }

        CRequirement& CRequirement::operator =(CRequirement&& other) noexcept {
            if (&other != this) {
                *this = std::move(other);
            }
            return *this;
        }

        CNode * CRequirement::clone() const {
            return new CRequirement(*this);
        }

        CRequirement::~CRequirement() {
        }

    }
    
}