descriptor Descriptor extends Component {
    internally requires {
        name : String;
        parentName : String;
        ports[] : PortDescription;
        architectureDefinition[]: ConnectionDescription;
        services[] : Service;
    }
    
    service getName() {
        return name;
    }
    service setName(newName) {
        name := newName;
    }

    service getParentName() {
        return parentName;
    }

    service setParentName(newParentName) {
        parentName := newParentName;
    }

    service getDescribedPortAt(index) {}

    service getDescribedConnAt(index) {}

    service getService(selector, arity) {}

    service new() {}
    service newNamed(name, superDesc) {}

    service addService(serviceComponent) {
        services := serviceComponent;
    }

    service removeService(selector, arity) {}

    service addPortDescription(pd) {
        connect default@pd to ports;
    }

    service removePortDescription(pd) {}

    service addConnDescription(cd) {
        connect default@cd to architectureDefinition;
    }

    service removeConnDescription(cd) {}
}
