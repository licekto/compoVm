descriptor PortDescription extends Component {
    internally requires {
        name : String;
        role : String;
        visibility : String;
        interfaceDefinition : Interface;
        kind : String;
        isCollectionPort : Bool;
    }

    service setName(name) {}
    service getName() {}
    service setRole(role) {}
    service getRole() {}
    service setKind(kind) {}
    service getKind() {}
    service setInterface(intf) {}
    service getInterface() {}
    service setVisibility(vis) {}
    service getVisibility() {}
    service setIsCollection(bool) {}
    service isCollection() {}
}
