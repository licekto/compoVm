descriptor Service extends Component {
    internally requires {
        serviceSign : ServiceSignature;
        tempsN[] : String;
        tempsV[] : Component;
        code : String;
    }

    service getName() {
        return serviceSign.getSelector();
    }
    
    service setName(selectorName) {
        serviceSign.setSelector(selectorName);
    }

    service addParam(param) {
        serviceSign.setParam(param);
    }

    service getParamAt(index) {
        serviceSign.getParamAt(index);
    }

    service setCode(newCode) {
        code := newCode;
    }

    service getCode(newCode) {
        return code;
    }

    service execute() {}
}
