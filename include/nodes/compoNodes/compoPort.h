#pragma once

#include "nodes/compoNode.h"
#include "nodes/proceduralNodes/compoSymbol.h"

namespace compo {
    
    /**
     * \class CCompoPort
     * \brief Class for port and inherited injected port nodes.
     * 
     * Class for port and inherited injected port nodes. Class inherits virtually from CCompoNode prevent diamond problem.
     * This class was designed because of the similar structure of port a injected port nodes thus to prevent code repetition.
     */
    class CCompoPort : public virtual CCompoNode {
    protected:
                CCompoSymbol                  * m_name;         /**< Name symbol of port */
                bool                            m_atomic;       /**< Is atomic? */

    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param name: Name of port
                                                * @param atomic: Is atomic?
                                                */
                                                CCompoPort          (CCompoSymbol *name = nullptr, bool atomic = false);
                                                
                                                /**
                                                * Copy constructor
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoPort          (const CCompoPort& other);
                                                
                                                /**
                                                * Move constructor
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoPort          (CCompoPort&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoPort&                     operator=           (const CCompoPort& other);
                
                                                /**
                                                * Move assignment operator
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoPort&                     operator=           (CCompoPort&& other) noexcept;
                
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                   () const;
                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoPort         ();
        
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print               (std::ostream& os) const;
        
                                                /**
                                                * Name getter
                                                * @return Name of port
                                                */
                std::string                     getName             () const;
                
                                                /**
                                                * Atomic getter
                                                * @return is atomic?
                                                */
                bool                            getAtomic           () const;
    };

}