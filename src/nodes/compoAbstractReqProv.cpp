#include "compoAbstractReqProv.h"

namespace compo {
    
    CCompoAbstractReqProv::CCompoAbstractReqProv(   visibilityType type,
                                                    const std::vector<CCompoPort*>& ports)
    : CCompoNode(NodeTypeEnum::PROVISION), m_intExtType(type), m_ports(ports)
    {}

    CCompoAbstractReqProv::~CCompoAbstractReqProv() {
        for (CCompoPort *port : m_ports) {
            delete port;
        }
    }

    void CCompoAbstractReqProv::print(std::ostream& outstream) const {
        outstream << "\t";
        if (m_intExtType == visibilityType::EXTERNAL) {
            outstream << "externally ";
        } else if (m_intExtType == visibilityType::INTERNAL) {
            outstream << "internally ";
        }

        outstream << "provides {" << std::endl;

        for (CCompoPort *port : m_ports) {
            outstream << "\t";;
            outstream << *port << std::endl;
        }

        outstream << "\t";;
        outstream << "}" << std::endl;
    }

    visibilityType CCompoAbstractReqProv::getVisibilityType() {
        return m_intExtType;
    }

    std::vector<CCompoPort*> * CCompoAbstractReqProv::getPorts() const {
        return const_cast<std::vector<CCompoPort*> *>(&m_ports);    // yuck
    }

}