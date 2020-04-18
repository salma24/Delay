#ifndef UNTITLED_CAPACITOR_H
#define UNTITLED_CAPACITOR_H

#include <string>
#include <iostream>

using namespace std;

class Capacitor {
private:
    string name;
    double value;
public:
    string getName() const;
    void setName(const string &name);

    double getValue() const;
    void setValue(double value);

    friend ostream& operator<<(ostream& os, const Capacitor& );

    Capacitor(string name, double value);
    Capacitor(const Capacitor& c);
    ~Capacitor();
};
#endif //UNTITLED_CAPACITOR_H
