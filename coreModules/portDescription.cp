descriptor PortDescription extends Component {
    provides { default : *; }
    internally requires {
        name : Symbol;
        role : Symbol;
        visibility : Symbol;
        interfaceDefinition : Interface;
        kind : Symbol;
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
