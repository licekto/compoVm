descriptor Interface extends Component {
    internally requires {
        type : String;
        signatures[] : ServiceSignature;
        connectedComponent : String;
    }
    service getType() {}
    service setType(type) {}
    service getSignaturesCount() {}
    service getSignatureAt(index) {}
    service setSignature(signature) {}
    service getConnectedComponent() {}
    service setConnectedComponent(component) {}
}
