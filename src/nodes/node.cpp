#include "nodes/node.h"

namespace nodes {

	CNode::CNode(types::nodeType type)
		: m_nodeType(type) {
	}

	types::nodeType CNode::getNodeType() const {
		return m_nodeType;
	}

	std::ostream& operator << (std::ostream& outstream, const CNode& node) {
		node.print(outstream);
		return outstream;
	}

}