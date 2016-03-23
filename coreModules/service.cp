descriptor Service extends Component {
    provides { default : *; }
    
    requires { context : Component; }

    internally requires {
        serviceSign : ServiceSignature;
        tempsN[] : Symbol;
        tempsV[] : *;
        code : AST;
    }

    service execute() {
        | bool1 bool2 |
        bool1 := $context.isConnected();
        bool1 := $paramsV.isConnected();
        if (bool1 & bool2) {
            /* Primitive execute */
        }
    }
}
