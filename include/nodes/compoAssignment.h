#pragma once

#include "compoNode.h"
#include "compoSymbol.h"

namespace compo {
    
    /**
     * \class CCompoAssignment
     * \brief Class for assignment representation.
     */
    class CCompoAssignment : public CCompoNode {
    private:
                CCompoSymbol                  * m_variable;     /**< Variable to assign to */
                CCompoNode                    * m_rValue;       /**< Right-hand side of assignment expression */

    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param variable: name of variable
                                                * @param rval: right-hand side of assignment
                                                */
                                                CCompoAssignment        (CCompoSymbol * variable = nullptr, CCompoNode * rVal = nullptr);
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoAssignment       ();
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print                   (std::ostream& os) const;
                                                /**
                                                * Variable name getter
                                                * @return Variable name
                                                */
        CCompoSymbol *                          getVariable             () const;
                                                /**
                                                * Right-hand side expression getter
                                                * @return Expression node
                                                */
        CCompoNode *                            getRValue               () const;
    };

}