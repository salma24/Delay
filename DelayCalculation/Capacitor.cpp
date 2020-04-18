#include "Capacitor.h"

Capacitor::Capacitor(string name, double value) {
    this->name=name;
    this->value=value;
}
Capacitor::Capacitor(const Capacitor& c) {
    this->name=c.name;
    this->value=c.value;
}
Capacitor::~Capacitor() {}
string Capacitor::getName() const {
    return name;
}
void Capacitor::setName(const string &name) {
    Capacitor::name = name;
}

double Capacitor::getValue() const {
    return value;
}

void Capacitor::setValue(double value) {
    Capacitor::value = value;
}

ostream& operator<<(ostream& os, const Capacitor& r){
    os <<"name: " <<r.getName()<< " value: " << r.getValue();
    return os;
}