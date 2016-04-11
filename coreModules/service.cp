descriptor Service extends Component {
    internally requires {
        serviceSign : ServiceSignature;
        tempsN[] : String;
        tempsV[] : *;
        code : String;
    }

    service execute() {}
}
