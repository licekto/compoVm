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
        ports := pd;
    }

    service removePortDescription(name) {}

    service addConnDescription(cd) {}

    service removeConnDescription(cd) {}
}
