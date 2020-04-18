#ifndef UNTITLED_RESISTOR_H
#define UNTITLED_RESISTOR_H

#include <string>
#include <iostream>

using namespace std;

class Resistor {
private:
    string name;
    double value;
public:
    string getName() const;
    void setName(const string &name);

    double getValue() const;
    void setValue(double value);

   friend ostream& operator<<(ostream& os, const Resistor& );

    Resistor(string name, double value);
    Resistor(const Resistor& r);
    ~Resistor();
};

#endif //UNTITLED_RESISTOR_H
