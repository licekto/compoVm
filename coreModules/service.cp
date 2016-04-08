descriptor Service extends Component {
    internally requires {
        serviceSign : ServiceSignature;
        tempsN[] : Symbol;
        tempsV[] : *;
        code : String;
    }

    service execute() {}
}
