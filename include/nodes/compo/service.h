#pragma once

#include "nodes/compo/abstractServConstr.h"

namespace nodes {

    namespace compo {

        /**
         * \class CCompoService
         * \brief Class for Compo service node representation.
         */
        class CService : public CAbstractServConstr {
        private:
                    std::vector<nodes::CNode*>        m_temporaries;      /**< Type of node */
        public:
                                                    /**
                                                    * Parametric constructor with default value
                                                    * @param name: Name symbol of service
                                                    * @param params: Vector of parameters
                                                    * @param body: Vector of body nodes
                                                    * @param temporaries: Vector of temporaries
                                                    */
                                                    CService       ( nodes::procedural::CSymbol* name = nullptr,
                                                                          const std::vector<nodes::procedural::CSymbol*>& params = std::vector<nodes::procedural::CSymbol*>(0),
                                                                          const std::vector<nodes::CNode*>& body = std::vector<nodes::CNode*>(0),
                                                                          const std::vector<nodes::CNode*>& temporaries = std::vector<nodes::CNode*>(0)  );

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CService       (const CService& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CService       (CService&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CService&                  operator =          (const CService& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CService&                  operator =          (CService&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual nodes::CNode *                    clone               () const;

                                                    /**
                                                     * Virtual destructor
                                                     */
            virtual                                 ~CService      ();

                                                    /**
                                                     * Number of temporaries getter
                                                     * @return number of temporaries
                                                     */
                    size_t                          getTemporariesSize  () const;
                                                    /**
                                                     * Temporaries getter
                                                     * @return constant pointer to temporaries
                                                     */
                    nodes::CNode *                    getTemporaryAt      (int index) const;

            virtual void                            print               (std::ostream& os) const;
        };

    }
    
}