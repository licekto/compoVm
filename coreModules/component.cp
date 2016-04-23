descriptor Component {
    provides { default : *; }
    
    requires {
            args[] : *;
            owner : Component;
            descriptorPort : Component;
    }
    
    internally provides {
        super : * ofKind SuperPort;
        self : * ofKind SelfPort;
    }
    service getPorts() {}
    service getPortNamed(newName) {}
    service getDescriptor() {
        return descriptorPort;
    }
    service getOwner() {
        return owner;
    }
    service getIdentityHash() {}
}
