descriptor Port extends Component {
    requires {
        owner : Component;
        connectedPorts[] : IPort;
        delegatedPorts[] : IPort;
    }

    internally requires {
        name : String;
        interfaceDescription : IInterface;
    }

    service getName() {}
    service getInterface() {}

    /* Primitive invoke */
    service invoke(serviceName) {}
    service isConnected() {}
    service isDelegated() {}

    /* Primitive connectTo*/
    service connectTo(port) {}
    service disconnectPort() {}
}
