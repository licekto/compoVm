descriptor Descriptor extends Component {
    internally requires {
        name : Symbol;
        ports[] : PortDescription;
        architectureDefinition[]: ConnectionDescription;
        services[] : Service;
    }
    
    service getDescribedPorts() {}
    service getDescribedConns() {}
    service getService(selector) {}

    service new() {}
    service newNamed(name, superDesc) {}

    service addService(serviceComponent) {}
    service removeService(selector, arity) {}

    service addPortDescription(pd) {}
    service removePortDescription(pd) {}

    service addConnDescription(cd) {}
    service removeConnDescription(cd) {}
}
