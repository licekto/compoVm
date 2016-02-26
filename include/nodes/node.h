#pragma once

#include <iostream>
#include <vector>

#include "nodes/types/nodeType.h"

/**
 *  \addtogroup nodes
 *  @{
 */

/**
 * nodes Namespace to uniquely identify compo AST nodes.
 */
namespace nodes {
    
    /**
     * \class CNode
     * \brief Abstract base class for other nodes.
     * 
     * Abstract base class of AST. Every node in AST is inherited from this one.
     * 
     * Rule of five is needed since CNode class has user-declared destructor.
     */
    class CNode {
    protected:
                types::nodeType                    m_nodeType;         /**< Type of node */
                
                                                /**
                                                * Parametric constructor with default value
                                                * @param type: type of node
                                                */
                                                CNode          (types::nodeType type = types::nodeType::END);
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CNode          (const CNode& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CNode          (CNode&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CNode&                     operator =          (const CNode& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CNode&                     operator =          (CNode&& other) noexcept;
    
    public:
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CNode *                    clone               () const = 0;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CNode         ();
        
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
        types::nodeType                            getNodeType         () const;
        
                                                /**
                                                * Overloaded output operator
                                                * Operator calls virtual print method inside because of inheritance.
                                                * @param os: output stream
                                                * @param node: node to print
                                                * @see print()
                                                * @return Altered output stream
                                                */
        friend  std::ostream&                   operator <<         (std::ostream& os, const CNode& node);
    };

}

/*! @}*/