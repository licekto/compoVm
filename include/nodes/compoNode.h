#pragma once

#include <iostream>
#include <vector>

#include "nodeType.h"

class CCompoNode {
protected:
            NodeTypeEnum        m_type;
            bool                m_toString;

public:
                                CCompoNode          (NodeTypeEnum type);
    virtual                     ~CCompoNode         () {};
    virtual void                print               (std::ostream& os) const = 0;
    friend  std::ostream&       operator <<         (std::ostream& os, const CCompoNode& node);
};
