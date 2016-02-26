#include "nodes/procedural/abstractPrimaryExpression.h"

namespace nodes {

    namespace procedural {

        CAbstractPrimaryExpression::CAbstractPrimaryExpression()
        : CNode(types::nodeType::CONSTANT),
          CAbstractExpression()
        {}

        CAbstractPrimaryExpression::CAbstractPrimaryExpression(const CAbstractPrimaryExpression& other)
        : CNode(other),
          CAbstractExpression() {
            *this = other;
        }

        CAbstractPrimaryExpression::CAbstractPrimaryExpression(CAbstractPrimaryExpression&& other) noexcept
        : CNode(std::move(other)),
          CAbstractExpression()
        {}

        CAbstractPrimaryExpression& CAbstractPrimaryExpression::operator =(const CAbstractPrimaryExpression& other) {
            if (&other != this) {
            }

            return *this;
        }

        CAbstractPrimaryExpression& CAbstractPrimaryExpression::operator =(CAbstractPrimaryExpression&& other) noexcept {
            if (&other != this) {
            }

            return *this;
        }

        CNode * CAbstractPrimaryExpression::clone() const {
            return new CAbstractPrimaryExpression(*this);
        }

        CAbstractPrimaryExpression::~CAbstractPrimaryExpression() {
        }

        void CAbstractPrimaryExpression::print(std::ostream& /*outstream*/) const {
        }

    }

}