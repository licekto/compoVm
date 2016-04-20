descriptor String {
    provides { default : *; }
    requires { args[] : *; }
    service new(stringValue) {}
}
