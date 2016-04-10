descriptor Port extends Component {
    requires {
        owner : Component;
        connectedPorts[] : Port;
        delegatedPorts[] : Port;
    }

    internally requires {
        name : String;
        interfaceDescription : Interface;
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
