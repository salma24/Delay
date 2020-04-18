#ifndef UNTITLED_NET_H
#define UNTITLED_NET_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h"

using namespace std;

class Net{
private:
    string name;
    Node* root;
public:
    Net();
    ~Net();
    vector<Node*> path;
    string getName() const;
    void setName(const string &name);
    Node* getRoot();
    int getNodesNum(Node* node);
    void set(Node* node,vector<double>& m,int & i);
    void sub(Node* node,vector<double>& m,int & i);
    void subCurr(Node* node);
    void setRoot(Node *root);
    void printNet(Node *node);
    void subSum(Node* node);
    double getDelay(Node* driver,Node* receiver);
    bool getPath(Node* driver,Node* receiver);
    void getMoments(int numOfMoments,vector<vector<double>>& res);
    void getMomentsAux(vector<double>& m);
    void init(Node* node);
};
double getDelay(Net* net,string filePath);

#endif //UNTITLED_NET_H
