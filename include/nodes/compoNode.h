#pragma once

#include <iostream>
#include <vector>

#include "nodeType.h"

/**
 *  \addtogroup compo
 *  @{
 */

/**
 * compo Namespace to uniquely identify compo AST nodes.
 */
namespace compo {
    
    /**
     * \class CCompoNode
     * \brief Abstract base class for other nodes.
     * 
     * Abstract base class of AST. Every node in AST is inherited from this one.
     */
    class CCompoNode {
    protected:
                NodeTypeEnum                    m_type;         /**< Type of node */

    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param type: type of node
                                                */
                                                CCompoNode          (NodeTypeEnum type = NodeTypeEnum::END);
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoNode         () {};
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print               (std::ostream& os) const = 0;
                                                /**
                                                * NodeType getter
                                                * @return Type of node
                                                */
        NodeTypeEnum                            getNodeType         () const;
                                                /**
                                                * Overloaded output operator
                                                * Operator calls virtual print method inside because of inheritance.
                                                * @param os: output stream
                                                * @param node: node to print
                                                * @see print()
                                                * @return Altered output stream
                                                */
        friend  std::ostream&                   operator <<         (std::ostream& os, const CCompoNode& node);
    };

}

/*! @}*/