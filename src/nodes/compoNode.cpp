#include "compoNode.h"

CCompoNode::CCompoNode(NodeTypeEnum type = NodeTypeEnum::END) : m_type(type) {}

NodeTypeEnum CCompoNode::getNodeType() const {
    return m_type;
}

std::ostream& operator << (std::ostream& os, const CCompoNode& node) {
    node.print(os);
    return os;
}