#pragma once

#include "compoNode.h"

class CCompoSymbol : public CCompoNode {
private:
            std::string         m_name;

public:
                                CCompoSymbol        (const std::string& name);
    virtual                     ~CCompoSymbol       () {};
    virtual void                print               (std::ostream& os) const;
            std::string         getName             () const;
};