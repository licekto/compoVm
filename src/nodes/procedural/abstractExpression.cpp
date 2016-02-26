#include "nodes/procedural/abstractExpression.h"

namespace nodes {

    namespace procedural {

        CAbstractExpression::CAbstractExpression()
        : CNode(types::nodeTypeEnum::CONSTANT)
        {}

        CAbstractExpression::CAbstractExpression(const CAbstractExpression& other)
        : CNode(other) {
            *this = other;
        }

        CAbstractExpression::CAbstractExpression(CAbstractExpression&& other) noexcept
        : CNode(std::move(other))
        {}

        CAbstractExpression& CAbstractExpression::operator =(const CAbstractExpression& other) {
            if (&other != this) {
            }

            return *this;
        }

        CAbstractExpression& CAbstractExpression::operator =(CAbstractExpression&& other) noexcept {
            if (&other != this) {
            }

            return *this;
        }

        CNode * CAbstractExpression::clone() const {
            return new CAbstractExpression(*this);
        }

        CAbstractExpression::~CAbstractExpression() {
        }

        void CAbstractExpression::print(std::ostream& /*outstream*/) const {
        }

    }

}