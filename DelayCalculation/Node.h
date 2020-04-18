#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include <string>
#include <vector>
#include <iostream>
#include "Resistor.h"
#include "Capacitor.h"

using namespace std;

class Node{
private:
    string            name;
    Capacitor*        c;
    bool              isInterface;
    double            subCsum;
    double            current;
    Node*             parent;
    vector<Resistor*>* edges;
    vector<Node*>*     sons;
public:
    Node();
    ~Node();
    string     getName() const;
    Capacitor* getC() const;
    bool   IsInterface() const;
    double getSubCsum() const;
    double getCurrent() const;
    Node*  getParent() const;
    vector<Resistor*>* getEdges();
    vector<Node*>*     getSons();

    void setName(const string &name);
    void setC(Capacitor *c);
    void setIsInterface(bool isInterface);
    void setSubCsum(double subCsum);
    void setCurrent(double current);
    void setParent(Node* parent);

    friend ostream &operator<<(ostream &os,Node &node);
};

#endif //UNTITLED_NODE_H
