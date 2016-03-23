descriptor ConnectionDescription extends Component {
    provides { default : *; }
    internally requires {
        sourceComponent : Symbol;
        sourcePort : Symbol;
        destinationComponent : Symbol;
        destinationPort : Symbol;
        isDisconnection : Bool;
    }

    service setSourceComponent(scd) {}
    service getSourceComponent() {}
    service setSourcePort(port) {}
    service getSourcePort() {}
    service setDestinationComponent(sdc) {}
    service getDestinationComponent() {}
    service setDestinationPort(port) {}
    service getDestinationPort() {}
    service setIsDisconnection(bool) {}
    service isDisconnection() {}
}
