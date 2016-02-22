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
     * 
     * Rule of five is needed since CCompoNode class has user-declared destructor.
     */
    class CCompoNode {
    protected:
                NodeTypeEnum                    m_nodeType;         /**< Type of node */
                
                                                /**
                                                * Parametric constructor with default value
                                                * @param type: type of node
                                                */
                                                CCompoNode          (NodeTypeEnum type = NodeTypeEnum::END);
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoNode          (const CCompoNode& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoNode          (CCompoNode&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoNode&                     operator =          (const CCompoNode& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoNode&                     operator =          (CCompoNode&& other) noexcept;
    
    public:
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone               () const = 0;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoNode         ();
        
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