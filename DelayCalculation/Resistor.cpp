#include "Resistor.h"

Resistor::Resistor(string name, double value) {
    this->name=name;
    this->value=value;
}
Resistor::Resistor(const Resistor& r) {
    this->name=r.name;
    this->value=r.value;
}

Resistor::~Resistor() {}

string Resistor::getName() const {
    return name;
}
void Resistor::setName(const string &name) {
    Resistor::name = name;
}

double Resistor::getValue() const {
    return value;
}

void Resistor::setValue(double value) {
    Resistor::value = value;
}

ostream& operator<<(ostream& os, const Resistor& r){
    os <<"name: " <<r.getName()<< " value: " << r.getValue();
    return os;
}

