#pragma once

#include <iostream>
#include <vector>

#include "nodeType.h"

class CCompoNode {
protected:
            NodeTypeEnum        m_type;

public:
                                CCompoNode          (NodeTypeEnum type = NodeTypeEnum::END);
    virtual                     ~CCompoNode         () {};
    virtual void                print               (std::ostream& os) const = 0;
    NodeTypeEnum                getNodeType         () const;
    friend  std::ostream&       operator <<         (std::ostream& os, const CCompoNode& node);
};
