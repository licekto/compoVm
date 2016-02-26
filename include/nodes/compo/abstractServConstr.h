#pragma once

#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

    namespace compo {

        /**
         * \class CAbstractServConstr
         * \brief Abstract base class for service and constraint nodes.
         * 
         * Abstract base class for service and constraint nodes. Class inherits virtually from CCompoNode prevent diamond problem.
         * This class was designed because of the similar structure of service a constraint nodes thus to prevent code repetition.
         */
        class CAbstractServConstr : public virtual CNode {
        protected:
                    nodes::procedural::CSymbol                  * m_name;         /**< Name */
                    std::vector<nodes::procedural::CSymbol*>      m_params;       /**< Vector of parameter names */
                    std::vector<nodes::CNode*>        m_body;         /**< Vector of body expressions */

                                                    /**
                                                    * Parametric constructor with default values
                                                    * Constructor is made protected to prevent from creation of object of this (abstract) type.
                                                    * @param name: Name of entity
                                                    * @param params: Vector of parameter names
                                                    * @param body: Vector of body expressions
                                                    */
                                                    CAbstractServConstr    ( nodes::procedural::CSymbol *name = nullptr,
                                                                                  const std::vector<nodes::procedural::CSymbol*>& params = std::vector<nodes::procedural::CSymbol*>(0),
                                                                                  const std::vector<nodes::CNode*>& body = std::vector<nodes::CNode*>(0)         );

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CAbstractServConstr    (const CAbstractServConstr& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CAbstractServConstr    (CAbstractServConstr&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAbstractServConstr&       operator =                  (const CAbstractServConstr& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAbstractServConstr&       operator =                  (CAbstractServConstr&& other) noexcept;

        public:
                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                       () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CAbstractServConstr  ();

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
                    nodes::CNode *                    getBodyNodeAt           (int index) const;

                                                    /**
                                                    * Body setter
                                                    * @param Constant pointer to vector with body expressions.
                                                    */
                    void                            setBodyNode             (nodes::CNode* bodyNode);

                                                    /**
                                                     * Parameter size vector size
                                                     * @return number of parameters
                                                     */
                    size_t                          getParamsSize           () const;

                                                    /**
                                                    * Parameters getter
                                                    * @return Constant pointer to vector with parameters.
                                                    */
                    nodes::procedural::CSymbol *                  getParamAt              (int index) const;

                                                    /**
                                                    * Parameters setter
                                                    * @param Constant pointer to pointer to parameter.
                                                    */
                    void                            setParam                (nodes::procedural::CSymbol *param);
        };

    }

}