descriptor Port extends Component {
    requires {
        connectedPorts[] : Port;
        delegatedPorts[] : Port;
    }

    internally requires {
        name : String;
        interfaceDescription : Interface;
        isCollection : Bool;
    }

    service getName() {}
    service getInterface() {}

    service invoke(serviceName) {}
    service isConnected() {}
    service isDelegated() {}

    service connectTo(port) {}
    service disconnectPort() {}

    service isCollectionPort() {}
}
