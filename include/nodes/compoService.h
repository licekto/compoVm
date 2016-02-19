#pragma once

#include "compoAbstractServConstr.h"

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
                                            CCompoService       (   CCompoSymbol* name = nullptr,
                                                                    const std::vector<CCompoSymbol*>& params = std::vector<CCompoSymbol*>(0),
                                                                    const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0),
                                                                    const std::vector<CCompoNode*>& temporaries = std::vector<CCompoNode*>(0)  );
                                            /**
                                            * Virtual destructor
                                            */
    virtual                                 ~CCompoService      ();
                                            /**
                                            * Temporaries getter
                                            * @return constant pointer to temporaries
                                            */
            std::vector<CCompoNode*> *      getTemporaries      () const;
};