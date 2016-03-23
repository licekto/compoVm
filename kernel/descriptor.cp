descriptor Descriptor extends Component {
    internally requires {
        name : Symbol;
        ports[] : PortDescription;
        architectureDefinition[]: ConnectionDescription;
        services[] : Service;
    }

    service getPorts() {}
    service getPortNamed(name) {}
    service getDescriptor() {}
    service getOwner() {}
    service getIndentityHash() {}
    
    service getDescribedPorts() {}
    service getDescribedConns() {}
    service getService() {}

    service new() {}
    service newNamed() {}

    service addService() {}
    service removeService(selector, arity) {}

    service addPortDescription(pd) {}
    service removePortDescription(pd) {}

    service addConnDescription(cd) {}
    service removeConnDescription(cd) {}
}
