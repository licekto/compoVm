#include "compoNode.h"

namespace compo {
    
    CCompoNode::CCompoNode(NodeTypeEnum type)
    : m_type(type)
    {}

    NodeTypeEnum CCompoNode::getNodeType() const {
        return m_type;
    }

    std::ostream& operator << (std::ostream& outstream, const CCompoNode& node) {
        node.print(outstream);
        return outstream;
    }

}