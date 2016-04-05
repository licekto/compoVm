descriptor Interface extends Component {
    provides {
        default : *;
    }
    internally requires {
        type : String;
        signatures[] : ServiceSignature;
        connectedComponent : String;
    }
    service getType() {}
    service setType(type) {}
    service getSignaturesCount() {}
    service getSignatureAt(index) {}
    service setSignatureAt(index) {}
    service getConnectedComponent() {}
    service setConnectedComponent() {}
}
