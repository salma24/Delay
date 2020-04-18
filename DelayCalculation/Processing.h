#ifndef UNTITLED_PROCESSING_H
#define UNTITLED_PROCESSING_H

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>
#include "Resistor.h"
#include "Capacitor.h"
#include "Node.h"
#include "Net.h"
using namespace std;

vector<string> split(const string& s, char c);
bool isValid(vector<string> res);
vector<string> getInput(ifstream& file);
vector<Node*> fillNodes(vector<string> input,string rootName);
Node* findNodeByName(vector<Node*> vec ,string name);
void ConnectNodes(vector<Node*> vec,vector<string> input);
//void AddRoots(vector<string> input,Net& net,vector<Node*> vec);

#endif //UNTITLED_PROCESSING_H
