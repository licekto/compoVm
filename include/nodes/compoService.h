#pragma once

#include "compoAbstractServConstr.h"

namespace compo {
    
    /**
     * \class CCompoService
     * \brief Class for Compo service node representation.
     */
    class CCompoService : public CCompoAbstractServConstr {
    private:
                std::vector<CCompoNode*>        m_temporaries;      /**< Type of node */
    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param name: Name symbol of service
                                                * @param params: Vector of parameters
                                                * @param body: Vector of body nodes
                                                * @param temporaries: Vector of temporaries
                                                */
                                                CCompoService       ( CCompoSymbol* name = nullptr,
                                                                      const std::vector<CCompoSymbol*>& params = std::vector<CCompoSymbol*>(0),
                                                                      const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0),
                                                                      const std::vector<CCompoNode*>& temporaries = std::vector<CCompoNode*>(0)  );
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoService       (const CCompoService& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoService       (CCompoService&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoService&                  operator =          (const CCompoService& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoService&                  operator =          (CCompoService&& other) noexcept;
    
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone               () const;
                                                
                                                /**
                                                 * Virtual destructor
                                                 */
        virtual                                 ~CCompoService      ();
        
                                                /**
                                                 * Number of temporaries getter
                                                 * @return number of temporaries
                                                 */
                size_t                          getTemporariesSize  () const;
                                                /**
                                                 * Temporaries getter
                                                 * @return constant pointer to temporaries
                                                 */
                CCompoNode *                    getTemporaryAt      (int index) const;
    };

}