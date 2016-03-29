descriptor Service extends Component {
    provides { default : *; }
    
    requires { context : Component; }

    internally requires {
        serviceSign : ServiceSignature;
        tempsN[] : Symbol;
        tempsV[] : *;
        code : String;
    }

    service execute() {}
}
