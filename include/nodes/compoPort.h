#pragma once

#include "compoNode.h"
#include "compoSymbol.h"

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
                                            * @return Name symbol of port
                                            */
            CCompoSymbol *                  getName             () const;
};