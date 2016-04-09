descriptor Interface extends Component {
    externally requires {
        component : Component;
        services[] : Service;
    }
    internally requires {
        type : String;
        signatures[] : ServiceSignature;
        componentName : String;
    }
    service getType() {}
    service setType(type) {}
    service getSignaturesCount() {}
    service getSignatureAt(index) {}
    service addSignature(signature) {}
    service getConnectedComponentName() {}
    service setConnectedComponentName(componentName) {}
    service getConnectedComponent() {}
    service setConnectedComponent(component) {}
    service getServiceAt(index) {}
    service addService(serviceComponent) {}
}
