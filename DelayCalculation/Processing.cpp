#include <algorithm>
#include <queue>
#include "Processing.h"

vector<string> split(const string& s, char c) {
    vector<string> v;
    unsigned int i = 0;
    unsigned int j = s.find(c);
    while (j < s.length()) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
        if (j >= s.length()) {
            v.push_back(s.substr(i, s.length()));
            break;
        }
    }
    return v;
}

bool isValid(vector<string> res){
    bool flag=true;
    if(!(regex_match(res[0],regex("(\\.MACRO) (.*)$")) && regex_match(res[res.size()-1],regex("\\.EOM$"))))flag=false;
    int count1=0,count2=0;
    for (int i = 1; i <res.size()-1 ; ++i) {
        if(regex_match(res[i],regex("(\\+)(.*)$"))) count1++;
        if(regex_match(res[i],regex("(.*) (.*) (.*) (.*)$"))) count2++;
    }
    if(count2 != (res.size()-2-count1)) flag=false;
    return flag;
}

vector<string> getInput(ifstream& file){
    vector<string> input;
    string str;
    while (getline(file, str)) {
        input.push_back(str);
    }
    return input;
}

vector<Node*> fillNodes(vector<string> input,string rootName){
    vector<string> nodes;
    vector<string> interfaces;
    //get all nodes names and interfaces
    nodes.push_back(rootName);

    for (int i = 0; i <input.size() ; ++i) {

        if (regex_match(input[i], regex("(.*) (.*) (.*) (.*)$"))) {
            if (!regex_match(input[i], regex("(.*) (.*) VSS (.*)$"))) {//VSS
                vector<string> tmp = split(input[i], ' ');
                if(find(nodes.begin(),nodes.end(),tmp[1]) == nodes.end()){
                    nodes.push_back(tmp[1]);
                }
                if(find(nodes.begin(),nodes.end(),tmp[2]) == nodes.end()){
                    nodes.push_back(tmp[2]);
                }

            }
        }
    }

    //get all nodes
    vector<Node*>  vec;
    vector<string> seen;
    queue<string>  turn;
    seen.push_back(rootName);
    turn.push(rootName);
    for (int i = 0; i <nodes.size() ; ++i) {

        Node *node = new Node();
        node->setName(nodes[i]);

        //flag indicates that single pin matches single capacitor
        int flag = 0;
        for (int j = 0; j < input.size(); ++j) {
            if (regex_match(input[j], regex("(.*) " + nodes[i] + " VSS (.*)$"))) {//VSS
                if (flag == 1) {
                    cout << "there are multiple capacitors for single pin" << endl;
                    exit(0);
                }
                vector<string> tmp = split(input[j], ' ');
                Capacitor *c1 = new Capacitor(tmp[0], stod(tmp[3]));
                node->setC(c1);
                node->setSubCsum(c1->getValue());
                flag = 1;
            }
        }
        if (flag == 0) {
            Capacitor *c1 = new Capacitor("", stod("1e-15"));
            node->setC(c1);
            node->setSubCsum(c1->getValue());
        }
        vec.push_back(node);
    }

    while(!turn.empty()){
        string next=turn.front();
        for (int j = 0; j < input.size(); ++j) {
            if (regex_match(input[j], regex("(.*) " + next + " (.*) (.*)$")) ||
                regex_match(input[j], regex("(.*) (.*) " + next + " (.*)$"))) {
                if (!regex_match(input[j], regex("(.*) " + next + " VSS (.*)$"))) {//VSS
                    vector<string> tmp = split(input[j], ' ');
                    string p = (tmp[2].compare(next) == 0) ? (tmp[1]) : (tmp[2]);
                    if (find(seen.begin(), seen.end(), tmp[0]) == seen.end()) {
                        Resistor *r = new Resistor(tmp[0], stod(tmp[3]));
                        findNodeByName(vec,next)->getEdges()->push_back(r);
                        turn.push(p);
                        seen.push_back(tmp[0]);

                    }
                }

            }
        }
        turn.pop();
    }

   return vec;
}

Node* findNodeByName(vector<Node*> vec ,string name){
    for (int i = 0; i <vec.size() ; ++i) {
        if(vec[i]->getName() == name){
            return vec[i];
        }
    }
  return NULL;
}

void ConnectNodes(vector<Node*> vec,vector<string> input){
    for (int i = 0; i <vec.size(); ++i) {
        for (int j = 0; j <(vec[i]->getEdges())->size() ; ++j) {
            string rName=(vec[i]->getEdges())->at(j)->getName();
            for (int k = 0; k < input.size(); ++k) {
                if (regex_match(input[k], regex(rName+" (.*) (.*) (.*)$"))) {
                    vector<string> tmp = split(input[k], ' ');
                    if(tmp[1].compare(vec[i]->getName()) == 0){
                            vec[i]->getSons()->push_back(findNodeByName(vec, tmp[2]));
                            Node *n=findNodeByName(vec, tmp[2]);
                            if(n != NULL) n->setParent(vec[i]);
                    }else {
                            vec[i]->getSons()->push_back(findNodeByName(vec, tmp[1]));
                            Node* n=findNodeByName(vec, tmp[1]);
                        if(n != NULL) n->setParent(vec[i]);
                    }
                }
            }
        }
    }
}
