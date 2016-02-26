#include "nodes/node.h"

namespace nodes {
    
    CNode::CNode(types::NodeTypeEnum type)
    : m_nodeType(type)
    {}
    
    CNode::CNode(const CNode& other)
    : m_nodeType(other.m_nodeType)
    {}
    
    CNode::CNode(CNode&& other) noexcept
    : m_nodeType(std::move(other.m_nodeType))
    {}
    
    CNode& CNode::operator =(const CNode& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
        }
        return *this;
    }

    CNode& CNode::operator =(CNode&& other) noexcept {
        if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
        }
        return *this;
    }
    
    CNode::~CNode() {
    }
    
    types::NodeTypeEnum CNode::getNodeType() const {
        return m_nodeType;
    }

    std::ostream& operator << (std::ostream& outstream, const CNode& node) {
        node.print(outstream);
        return outstream;
    }

}