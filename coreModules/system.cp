descriptor System extends Component {
    internally requires {
        name : String;
    }
    service println(string) {}
    service print(string) {}
    service readString() {}
    service readLine() {}
    service readInt() {}
    service getRand(seed) {}
}

