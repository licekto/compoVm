#pragma once

#include "compoNode.h"

namespace compo {
    
    /**
     * \class CCompoFor
     * \brief Class for for-loop representation
     */
    class CCompoFor : public CCompoNode {
    private:
                CCompoNode                    * m_startCondition;           /**< Start condition node */
                CCompoNode                    * m_endCondition;             /**< Start condition node */
                CCompoNode                    * m_step;                     /**< Step node */
                std::vector<CCompoNode*>        m_body;                     /**< Body nodes vector */

    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param startCond: Star condition node pointer
                                                * @param endCond: Star condition node pointer
                                                * @param step: Step node pointer
                                                * @param body: Reference to vector of body nodes
                                                */
                                                CCompoFor           (   CCompoNode *startCond = nullptr,
                                                                        CCompoNode *endCond = nullptr,
                                                                        CCompoNode *step = nullptr,
                                                                        const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0));
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoFor          ();
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print               (std::ostream& os) const;
                                                /**
                                                * Body getter
                                                * @return Constant pointer to body vector
                                                */
                std::vector<CCompoNode*> *      getBody             () const;
                                                /**
                                                * Start condition getter
                                                * @return Pointer to start condition node
                                                */
                CCompoNode *                    getStartCond        () const;
                                                /**
                                                * End condition getter
                                                * @return Pointer to end condition node
                                                */
                CCompoNode *                    getEndCond          () const;
                                                /**
                                                * Step getter
                                                * @return Pointer to step node
                                                */
                CCompoNode *                    getStep             () const;
    };

}