#include "compoNode.h"

namespace compo {
    
    CCompoNode::CCompoNode(NodeTypeEnum type)
    : m_nodeType(type)
    {}

    NodeTypeEnum CCompoNode::getNodeType() const {
        return m_nodeType;
    }

    std::ostream& operator << (std::ostream& outstream, const CCompoNode& node) {
        node.print(outstream);
        return outstream;
    }

}