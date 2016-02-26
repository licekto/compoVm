#pragma once

#include "nodes/compoNode.h"
#include "nodes/proceduralNodes/compoSymbol.h"

namespace compo {

    /**
     * \class CCompoDescriptor
     * \brief Class for Compo descriptor representation.
     */
    class CCompoDescriptor : public CCompoNode {
    private:
                CCompoSymbol                  * m_name;         /**< Descriptor name */
                CCompoSymbol                  * m_extends;      /**< Inheritance information */
                std::vector<CCompoNode*>        m_body;         /**< Vector of descriptor body nodes */

    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param name: Name of descriptor
                                                * @param extends: Name of parent descriptor
                                                * @param body: Vector of body nodes
                                                */
                                                CCompoDescriptor    (   CCompoSymbol *name = nullptr,
                                                                        CCompoSymbol *extends = nullptr,
                                                                        const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0));
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoDescriptor    (const CCompoDescriptor& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoDescriptor    (CCompoDescriptor&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoDescriptor&               operator =          (const CCompoDescriptor& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoDescriptor&               operator =                  (CCompoDescriptor&& other) noexcept;
    
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                       () const;
                                                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoDescriptor   ();
        
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print               (std::ostream& os) const;
        
                                                /**
                                                * Name getter
                                                * @return Name symbol 
                                                */
                std::string                     getName             () const;
                
                                                /**
                                                * Extends setter
                                                * @param Name of parent class symbol 
                                                */
                void                            setExtends          (CCompoSymbol * extends);
                
                                                /**
                                                * Extends getter
                                                * @return Name of parent class symbol 
                                                */
                std::string                     getExtends          () const;
                
                                                /**
                                                 * Body vector size getter
                                                 * @return number of elements in body
                                                 */
                size_t                          getBodySize         () const;
                
                                                /**
                                                * Body getter
                                                * @return Constant pointer to body vector
                                                */
                CCompoNode *                    getBodyNodeAt       (int index) const;
    };

}