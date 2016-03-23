descriptor ServiceSignature extends Component {
    provides { default : *; }

    internally requires {
        name : Symbol;
        paramNames[] : Symbol;
    }
}
