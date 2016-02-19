#pragma once

#include "compoNode.h"
#include "compoPort.h"
#include "visibilityType.h"

/**
 * \class CCompoAbstractReqProv
 * \brief Abstract base class for requirement and provision nodes.
 * 
 * Abstract base class for requirement and provision nodes. Class inherits virtually from CCompoNode prevent diamond problem.
 * This class was designed because of the same structure of provision a requirement nodes thus to prevent code repetition.
 */
class CCompoAbstractReqProv : public virtual CCompoNode {
protected:
            visibilityType                  m_intExtType;       /**< Type of visibility */
            std::vector<CCompoPort*>        m_ports;            /**< Vector of ports */
            
                                            /**
                                            * Parametric constructor with default values
                                            * Constructor is made protected to prevent from creation of object of this (abstract) type.
                                            * @param type: type of visibilty
                                            * @param ports: vector of ports
                                            */
                                            CCompoAbstractReqProv   (   visibilityType type = visibilityType::EXTERNAL,
                                                                        const std::vector<CCompoPort*>& ports = std::vector<CCompoPort*>(0));
                                            
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
                                            * Ports vector getter
                                            * @return vector of ports
                                            */
            std::vector<CCompoPort*> *      getPorts                () const;
};
