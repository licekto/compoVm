descriptor Int {
    provides { default : *; }
    requires { args[] : *; }
    service new(stringValue) {}
}
