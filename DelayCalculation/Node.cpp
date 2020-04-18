#include "Node.h"

Node::Node() {
    this->name="";
    this->c=NULL;
    this->isInterface=false;
    this->subCsum=0;
    this->current=1.0;
    this->parent=NULL;
    this->edges=new vector<Resistor*>();
    this->sons=new vector<Node*>();
}
//this method assumes that the resistors and capacitors are dynamically allocated
Node::~Node() {
    delete this->getEdges();
    delete this->getSons();
    delete this->getC();
}
string Node::getName() const {
    return this->name;
}
Capacitor* Node::getC() const {
    return this->c;
}
bool Node::IsInterface() const {
    return this->isInterface;
}
double Node::getSubCsum() const {
    return this->subCsum;
}
double Node::getCurrent() const {
    return this->current;
}
Node* Node::getParent() const {
    return this->parent;
}
vector<Resistor*>* Node::getEdges(){
    return this->edges;
}
vector<Node*>*     Node::getSons(){
    return this->sons;
}

void Node::setName(const string &name) {
    Node::name = name;
}
void Node::setC(Capacitor *c) {
    Node::c = c;
}
void Node::setIsInterface(bool isInterface) {
    Node::isInterface = isInterface;
}
void Node::setSubCsum(double subCsum) {
    Node::subCsum = subCsum;
}
void Node::setCurrent(double current) {
    Node::current = current;
}
void Node::setParent(Node *parent) {
    Node::parent = parent;
}

ostream &operator<<(ostream &os,Node &node) {
    os<<"***********************start***************"<<'\n';
    os << "name: " << node.name<<'\n';
    if(node.getC() == NULL){
        os<<" c: " << "NULL"<<'\n';
    }else{
        os <<" c: " << *(node.getC())<<'\n' ;
    }
    os << " Current: " << node.getCurrent()  <<'\n';
    os << " isInterface: " << node.IsInterface()  <<'\n';
    os << " sub C sum: "<< node.getSubCsum()<<'\n';
    if(node.getParent() == NULL){
        os<<" parent: " << "NULL"<<'\n';
    }else{
        os <<" parent: " << (node.getParent())->getName()<<'\n' ;
    }
    for (int i = 0; i < (node.getEdges())->size(); ++i) {
        os <<" edge["<< i <<"]:{" << *((node.getEdges())->at(i))<<"}, son["<< i <<"]: " << ((node.getSons())->at(i)->getName())<<'\n' ;
    }
    os<<"***********************end*****************"<<'\n';
    return os;
}
