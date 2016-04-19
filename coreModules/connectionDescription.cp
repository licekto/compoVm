descriptor ConnectionDescription extends Component {
    internally requires {
        sourceType : String;
        sourceComponent : String;
        sourceComponentIndex : UInt;
        sourceComponentInvocation : ServiceInvocation;
        sourcePort : String;

        destinationType : String;
        destinationComponent : String;
        destinationComponentIndex : UInt;
        destinationComponentInvocation : ServiceInvocation;
        destinationPort : String;

        bindType : String;
    }

    service setSourceType(type) {}
    service getSourceType() {}
    service setSourceComponent(scd) {}
    service getSourceComponent() {}
    service setSourceComponentIndex(index) {}
    service getSourceComponentIndex() {}
    service setSourceComponentInvocation(inv) {}
    service getSourceComponentInvocation() {}

    service setSourcePort(port) {}
    service getSourcePort() {}

    service setDestinationType(type) {}
    service getDestinationType() {}
    service setDestinationComponent(sdc) {}
    service getDestinationComponent() {}
    service setDestinationComponentIndex(index) {}
    service getDestinationComponentIndex() {}
    service setDestinationComponentInvocation(inv) {}
    service getDestinationComponentInvocation() {}

    service setDestinationPort(port) {}
    service getDestinationPort() {}

    service setBindType(type) {}
    service getBindType() {}
}
