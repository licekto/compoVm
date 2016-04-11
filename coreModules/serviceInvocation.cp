descriptor ServiceInvocation extends Component {
    internally requires {
        receiver : String;
        selector : String;
        params[] : Component;
    }
    service setReceiver(receiver) {}
    service getReceiver() {}
    service setSelector(selector) {}
    service getSelector() {}
    service getParamsCount() {}
    service getParamAt(index) {}
    service addParam(param) {}
}
