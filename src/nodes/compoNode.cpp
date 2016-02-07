#include "compoNode.h"

CCompoNode::CCompoNode(NodeTypeEnum type = NodeTypeEnum::END) : m_type(type), m_toString(true) {}

std::ostream& operator << (std::ostream& os, const CCompoNode& node) {
    node.print(os);
    return os;
}