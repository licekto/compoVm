descriptor ServiceSignature extends Component {
    internally requires {
        selector : String;
        paramNames[] : String;
    }
    service setSelector(name) {}
    service getSelector() {}
    service getParamsCount() {}
    service getParamAt(index) {}
    service setParam(param) {}
}
