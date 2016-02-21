#pragma once

#include "compoNode.h"
#include "compoSymbol.h"

namespace compo {
    
    /**
     * \class CCompoAbstractServConstr
     * \brief Abstract base class for service and constraint nodes.
     * 
     * Abstract base class for service and constraint nodes. Class inherits virtually from CCompoNode prevent diamond problem.
     * This class was designed because of the similar structure of service a constraint nodes thus to prevent code repetition.
     */
    class CCompoAbstractServConstr : public virtual CCompoNode {
    protected:
                CCompoSymbol                  * m_name;         /**< Name */
                std::vector<CCompoSymbol*>      m_params;       /**< Vector of parameter names */
                std::vector<CCompoNode*>        m_body;         /**< Vector of body expressions */

                                                /**
                                                * Parametric constructor with default values
                                                * Constructor is made protected to prevent from creation of object of this (abstract) type.
                                                * @param name: Name of entity
                                                * @param params: Vector of parameter names
                                                * @param body: Vector of body expressions
                                                */
                                                CCompoAbstractServConstr   (    CCompoSymbol *name = nullptr,
                                                                                const std::vector<CCompoSymbol*>& params = std::vector<CCompoSymbol*>(0),
                                                                                const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0)         );

    public:
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoAbstractServConstr  ();
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print                   (std::ostream& os) const;
                                                /**
                                                * Name getter
                                                * @return Name of entity
                                                */
                CCompoSymbol *                  getName                 () const;
                                                /**
                                                * Body getter
                                                * @return Constant pointer to vector with body expressions.
                                                */
                std::vector<CCompoNode*> *      getBody                 () const;
                                                /**
                                                * Body setter
                                                * @param Constant pointer to vector with body expressions.
                                                */
                void                            setBody                 (const std::vector<CCompoNode*>& body);
                                                /**
                                                * Parameters getter
                                                * @return Constant pointer to vector with parameters.
                                                */
                std::vector<CCompoSymbol*> *    getParams               () const;
                                                /**
                                                * Parameters setter
                                                * @param Constant pointer to pointer to parameter.
                                                */
                void                            setParam                (CCompoSymbol *param);
    };

}