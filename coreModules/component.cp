descriptor Component {
    provides { default : *; }
    
    requires {
            args[] : *;
            owner : Component;
    }
    
    internally provides {
        super : * ofKind SuperPort;
        self : * ofKind SelfPort;
    }

    service getPorts() {}
    service getPortNamed(name) {}
    service getDescriptor() {}
    service getOwner() {}
    service getIdentityHash() {}
}
