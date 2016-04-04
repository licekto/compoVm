descriptor ServiceSignature extends Component {
    provides { default : *; }

    internally requires {
        name : Symbol;
        paramNames[] : Symbol;
    }
    service setSelector(name) {}
    service getSelector() {}
    service getParamsCount() {}
    service getParamName(index) {}
    service setParamName(index, name) {}
}
