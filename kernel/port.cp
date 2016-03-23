descriptor Port extends Component {
    requires {
        owner : IComponent;
        connectedPorts[] : IPort;
        delegatedPorts[] : IPort;
    }

    internally requires {
        name : IString;
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
