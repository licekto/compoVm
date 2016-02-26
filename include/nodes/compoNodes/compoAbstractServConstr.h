#pragma once

#include "nodes/compoNode.h"
#include "nodes/proceduralNodes/compoSymbol.h"

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
                                                CCompoAbstractServConstr    ( CCompoSymbol *name = nullptr,
                                                                              const std::vector<CCompoSymbol*>& params = std::vector<CCompoSymbol*>(0),
                                                                              const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0)         );
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoAbstractServConstr    (const CCompoAbstractServConstr& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoAbstractServConstr    (CCompoAbstractServConstr&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoAbstractServConstr&       operator =                  (const CCompoAbstractServConstr& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoAbstractServConstr&       operator =                  (CCompoAbstractServConstr&& other) noexcept;
    
    public:
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                       () const;

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
                std::string                     getName                 () const;
                
                                                /**
                                                 * Body size vector size
                                                 * @return number of elements in body
                                                 */
                size_t                          getBodySize             () const;
                
                                                /**
                                                * Body getter
                                                * @return Constant pointer to vector with body expressions.
                                                */
                CCompoNode *                    getBodyNodeAt           (int index) const;
                
                                                /**
                                                * Body setter
                                                * @param Constant pointer to vector with body expressions.
                                                */
                void                            setBodyNode             (CCompoNode* bodyNode);
                
                                                /**
                                                 * Parameter size vector size
                                                 * @return number of parameters
                                                 */
                size_t                          getParamsSize           () const;
                
                                                /**
                                                * Parameters getter
                                                * @return Constant pointer to vector with parameters.
                                                */
                CCompoSymbol *                  getParamAt              (int index) const;
                
                                                /**
                                                * Parameters setter
                                                * @param Constant pointer to pointer to parameter.
                                                */
                void                            setParam                (CCompoSymbol *param);
    };

}