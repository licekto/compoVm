descriptor CollectionPort extends Port {
    service invoke(serviceName, index) {}
    service disconnectPort(index) {}
}
