descriptor Component {
    provides { default : *; }
    
    requires { args[] : *; }
    
    internally requires {
        super : * ofKind SuperPort;
        self : * ofKind SelfPort;
    }

    service getPorts() {}
    service getPortNamed(name) {}
    service getDescriptor() {}
    service getOwner() {}
    service getIndentityHash() {}
}
