#pragma once

#include "compoNode.h"

class CCompoFor : public CCompoNode {
private:
    CCompoNode                * m_startCondition;
    CCompoNode                * m_endCondition;
    CCompoNode                * m_step;
    std::vector<CCompoNode*>    m_body;
    
public:
                                        CCompoFor           (CCompoNode *startCond = nullptr, CCompoNode *endCond = nullptr, CCompoNode *step = nullptr, std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0));
    virtual                             ~CCompoFor          ();
    virtual void                        print               (std::ostream& os) const;
            std::vector<CCompoNode*> *  getBody             () const;
            CCompoNode *                getStartCond        () const;
            CCompoNode *                getEndCond          () const;
            CCompoNode *                getStep             () const;
};