#pragma once

#include "compoAbstractReqProv.h"

/**
 * \class CCompoRequirement
 * \brief Class for Compo requirement node representation.
 */
class CCompoRequirement : public CCompoAbstractReqProv {            
public:
                                            /**
                                            * Parametric constructor with default value
                                            * @param type: Type of visibility
                                            * @param ports: Vector of ports
                                            */
                                            CCompoRequirement     ( visibilityType type = visibilityType::EXTERNAL,
                                                                    const std::vector<CCompoPort*>& ports = std::vector<CCompoPort*>(0));
                                            /**
                                            * Virtual destructor
                                            */
    virtual                                 ~CCompoRequirement    ();
};