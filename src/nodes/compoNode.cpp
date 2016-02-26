#include "nodes/compoNode.h"

namespace compo {
    
    CCompoNode::CCompoNode(NodeTypeEnum type)
    : m_nodeType(type)
    {}
    
    CCompoNode::CCompoNode(const CCompoNode& other)
    : m_nodeType(other.m_nodeType)
    {}
    
    CCompoNode::CCompoNode(CCompoNode&& other) noexcept
    : m_nodeType(std::move(other.m_nodeType))
    {}
    
    CCompoNode& CCompoNode::operator =(const CCompoNode& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
        }
        return *this;
    }

    CCompoNode& CCompoNode::operator =(CCompoNode&& other) noexcept {
        if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
        }
        return *this;
    }
    
    CCompoNode::~CCompoNode() {
    }
    
    NodeTypeEnum CCompoNode::getNodeType() const {
        return m_nodeType;
    }

    std::ostream& operator << (std::ostream& outstream, const CCompoNode& node) {
        node.print(outstream);
        return outstream;
    }

}