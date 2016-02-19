#pragma once

#include "compoAbstractServConstr.h"

/**
 * \class CCompoConstraint
 * \brief Class for Compo constraint representation.
 */
class CCompoConstraint : public CCompoAbstractServConstr {
public:
                                            /**
                                            * Parametric constructor with default values
                                            * @param name: Name of constraint
                                            * @param params: Vector of parameters
                                            * @param body: Vector of body expressions
                                            */
                                            CCompoConstraint    (   CCompoSymbol *name = nullptr,
                                                                    const std::vector<CCompoSymbol*>& params = std::vector<CCompoSymbol*>(0),
                                                                    const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0));
                                            /**
                                            * Virtual destructor
                                            */
    virtual                                 ~CCompoConstraint   ();
};