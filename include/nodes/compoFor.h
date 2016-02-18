#pragma once

#include "compoNode.h"

class CCompoFor : public CCompoNode {
private:
    CCompoNode                * m_startCondition;
    CCompoNode                * m_endCondition;
    CCompoNode                * m_step;
    std::vector<CCompoNode*>    m_body;
    
public:
                                CCompoFor           ();
                                ~CCompoFor          ();
    std::vector<CCompoNode*> *  getBody             () const;
};