#pragma once

#include <exception>

#include "compoNode.h"
#include "compoPort.h"
#include "visibilityType.h"

namespace compo {
    
    /**
     * \class CCompoAbstractReqProv
     * \brief Abstract base class for requirement and provision nodes.
     * 
     * Abstract base class for requirement and provision nodes. Class inherits virtually from CCompoNode prevent diamond problem.
     * This class was designed because of the same structure of provision a requirement nodes thus to prevent code repetition.
     */
    class CCompoAbstractReqProv : public virtual CCompoNode {
    protected:
                visibilityType                  m_visibilityType;   /**< Type of visibility */
                std::vector<compo::CCompoPort*> m_ports;            /**< Vector of ports */

                                                /**
                                                * Parametric constructor with default values
                                                * Constructor is made protected to prevent from creation of object of this (abstract) type.
                                                * @param type: type of visibilty
                                                * @param ports: vector of ports
                                                */
                                                CCompoAbstractReqProv   (   visibilityType type = visibilityType::EXTERNAL,
                                                                            const std::vector<CCompoPort*>& ports = std::vector<CCompoPort*>(0));
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param rp: reference to another object of same type
                                                */
                                                CCompoAbstractReqProv   (const CCompoAbstractReqProv& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param rp: rvalue-reference to another object of same type
                                                */
                                                CCompoAbstractReqProv   (CCompoAbstractReqProv&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param rp: reference to another object of same type
                                                * @return reference to assigned object
                                                */
    CCompoAbstractReqProv&                      operator =              (const CCompoAbstractReqProv& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param rp: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
    CCompoAbstractReqProv&                      operator =              (CCompoAbstractReqProv&& other) noexcept;

    public:
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoAbstractReqProv  ();
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print                   (std::ostream& os) const;
                                                /**
                                                * visibilityType getter
                                                * @return Type of visibility
                                                */
                visibilityType                  getVisibilityType       ();
                
                                                /**
                                                * Number of ports getter
                                                * @return number of ports of requirement
                                                */
                size_t                          getNumberOfPorts        () const;

                                                /**
                                                * Ports getter
                                                * @return Port at given index
                                                */                
                CCompoPort *                    getPortAt               (unsigned int index) const;
    };

}