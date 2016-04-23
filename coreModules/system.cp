descriptor System extends Component {
    internally requires {
        name : String;
    }
    service println(string) {}
    service readString() {}
    service readInt() {}
    service getRand(seed) {}
}

