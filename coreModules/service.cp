descriptor Service extends Component {
    internally requires {
        serviceSign : ServiceSignature;
        tempsN[] : String;
        tempsV[] : Component;
        code : String;
    }

    service execute() {}
}
