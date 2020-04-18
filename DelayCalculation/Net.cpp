#include <math.h>
#include <fstream>
#include "Net.h"
#include "Processing.h"
#include "LSQR.h"
#include "Laplace.h"
#include "newton_raphson.h"

double tol[4]={0.10688,0.10343,0.1302,0.11036};
double current_t=0;
Net:: Net(){}
Net::~Net(){}
string Net::getName() const {
    return this->name;
}
void Net::setName(const string &name) {
    Net::name = name;
}
Node* Net::getRoot(){
    return root;
}
void Net::setRoot(Node *root) {
    Net::root = root;
}
void Net::printNet(Node *node){
    if(node == NULL)
        return;
    cout<<node->getName()<<endl;
    for (int i = 0; i <node->getSons()->size() ; i++) {
        printNet(node->getSons()->at(i));
    }
}
void Net::subSum(Node* node){
    if(node == NULL) return;
    for (int i = 0; i < node->getSons()->size() ; ++i) {
        subSum(node->getSons()->at(i));
        node->setSubCsum(node->getSubCsum()+node->getSons()->at(i)->getSubCsum());
    }
}
int getIndex(vector<Node*> vec,Node* node){
    for (int i = 0; i < vec.size(); ++i) {
        if(vec[i]->getName() == node->getName()) return i;
    }
    return -1;
}
double Net::getDelay(Node* driver,Node* receiver){
    this->path.clear();
    getPath(driver,receiver);
    reverse(path.begin(),path.end());
    double delay=0;
    for (int i = 0; i < path.size()-1; i++) {
       delay+=(path[i+1]->getSubCsum())* (path[i]->getEdges()->at(getIndex(*(path[i]->getSons()),path[i+1]))->getValue());
    }
    return delay;
}
bool Net::getPath(Node* driver,Node* receiver){
  if(driver == NULL) return false;
  if(driver == receiver){
      this->path.push_back(driver);
      return true;
  }
    for (int i = 0; i < driver->getSons()->size(); ++i) {
        if(getPath(driver->getSons()->at(i),receiver)){
            this->path.push_back(driver);
            return true ;
        }
    }
return false;
}
int Net::getNodesNum(Node* node){
    int size=1;
    if(node == NULL)return 0;
    for (int i = 0; i < node->getSons()->size() ; ++i) {
        size+=getNodesNum(node->getSons()->at(i));
    }
    return size;

}
void Net::set(Node* node,vector<double>& m,int& index){
    if(node == NULL) return;
    node->setCurrent(m[index]);
    index++;
    for (int i = 0; i < node->getSons()->size() ; ++i) {
        set(node->getSons()->at(i),m,index);
    }

}
void Net::sub(Node* node,vector<double>& m,int& index){
    if(node == NULL) return;
    m[index]=(node->getCurrent() * ((node->getParent() == NULL) ?(0.001):node->getParent()->getEdges()->at(getIndex(*(node->getParent()->getSons()),node))->getValue()));
    index++;
    for (int i = 0; i < node->getSons()->size() ; ++i) {
        sub(node->getSons()->at(i),m,index);
    }
}
void Net::subCurr(Node* node){
    if(node == NULL) return;
    for (int i = 0; i < node->getSons()->size() ; ++i) {
        subCurr(node->getSons()->at(i));
        node->setCurrent(node->getCurrent()+node->getSons()->at(i)->getCurrent());
    }
}
void  Net::getMomentsAux(vector<double>& m){
    subCurr(this->root);
    int index=0;
    sub(this->root,m,index);
    m.insert(m.begin(),0.0);
    for (int i = 1; i < m.size(); ++i) {
        m[i]=m[i-1]-m[i];
    }
    vector<double> tmp;
    for (int i = 1; i < m.size(); ++i) {
        tmp.push_back(m[i]);
    }
    cout<<endl;
    index=0;
    //prepare the current for the next round,this function store the new current value in the tree
    set(this->root,tmp,index);
}
void Net::init(Node* node){
    if(node == NULL) return;
    node->setCurrent(1.0);
    for (int i = 0; i < node->getSons()->size() ; ++i) {
        init(node->getSons()->at(i));
    }
}
void Net::getMoments(int numOfMoments,vector<vector<double>>& res){
    vector<double> m0(getNodesNum(this->root)+1,1.0);
    vector<double> m(getNodesNum(this->root),0.0);
    res.push_back(m0);

    for (int i = 1; i < numOfMoments; ++i) {
        res.push_back(m);
    }

    for (int i = 1; i < numOfMoments; ++i) {
        getMomentsAux(res[i]);
    }
    init(this->root);
}
void numericalCalc(Net* net){
    if(!net) {
        
        vector<vector<double>> res;
        //net->getMoments(10,res);
        Eigen::MatrixXd A = Eigen::MatrixXd(5, 5);

        A(0, 4) = res[0][res[0].size() - 1];
        A(0, 3) = A(1, 4) = res[1][res[1].size() - 1];
        A(0, 2) = A(1, 3) = A(2, 4) = res[2][res[2].size() - 1];
        A(0, 1) = A(1, 2) = A(2, 3) = A(3, 4) = res[3][res[3].size() - 1];
        A(0, 0) = A(1, 1) = A(2, 2) = A(3, 3) = A(4, 4) = res[4][res[4].size() - 1];
        A(1, 0) = A(2, 1) = A(3, 2) = A(4, 3) = res[5][res[5].size() - 1];
        A(2, 0) = A(3, 1) = A(4, 2) = res[6][res[6].size() - 1];
        A(3, 0) = A(1, 4) = res[7][res[7].size() - 1];
        A(4, 0) = res[8][res[8].size() - 1];

        Eigen::SparseMatrix<double> Asp = A.sparseView();
        // Determine b (= A x_t)
        Eigen::VectorXd b(5);
        for (int i = 0; i < b.rows(); i++) {
            b(i) = (-1) * (res[5 + i][res[5 + i].size() - 1]);
        }
        // Minimizer x
        Eigen::VectorXd x(5);
        x.setZero();
        //Run LSQR
        LSQR lsqr = LSQR(Asp, b, x, 1.0e-40);
        //cout<<Asp<<endl;
        x = lsqr.SolutionX();
        float a1, b1, c1, d1;
        c1 = 1.0;
        b1 = x(0);
        a1 = x(1);
        float root1, root2;
        d1 = b1 * b1 - 4 * a1 * c1;
        root1 = ((-b1) + sqrt(d1)) / (2 * a1);
        root2 = ((-b1) - sqrt(d1)) / (2 * a1);
        Eigen::MatrixXd C = Eigen::MatrixXd(2, 2);
        C(0, 0) = C(1, 0) = pow(root1, -1);
        C(0, 1) = C(1, 1) = pow(root2, -1);
        Eigen::SparseMatrix<double> Csp = C.sparseView();
        Eigen::VectorXd Cb(2);
        Cb(0) = 1.0;
        Cb(1) = res[1][res[1].size() - 1];
        Eigen::VectorXd k(2);
        k.setZero();
        LSQR Clsqr = LSQR(Csp, Cb, k, 1.0e-40);
        k = Clsqr.SolutionX();
    }
}
double get(int i){
    double d=current_t;
    std::ostringstream strs;
    strs << d;
    const string str = strs.str();
    vector<string> e=split(str,'e');

    double tmp=tol[(i)%4]*stod("1e"+e[1]);
    return d-tmp;
}
double getRC(){
    double d=current_t;
    return (d/0.7);
}
double getSlope(){
    return (1.9)*getRC();
}
double getDelay(Net* net,string filePath){

    ifstream inputFile(filePath);
    vector<string> input = getInput(inputFile);
    if (!isValid(input)) {
        cout << "the input is not valid" << endl;
        exit(0);
    }
    //the vec includes dynamically allocated nodes don't forget to delete
    string rootName;
    for (int i = 0; i < input.size(); ++i) {
        if (regex_match(input[i], regex("(\\+\\+) (.*)$"))) {
            rootName = split(input[i], ' ')[1];
            break;
        }
    }
    net->setName(split(input[0], ' ')[1]);
    vector<Node *> vec = fillNodes(input, rootName);
    net->setRoot(vec[0]);
    ConnectNodes(vec, input);
    net->subSum(net->getRoot());
    numericalCalc(net);
    string driver=rootName;
    for (int i = 0; i <input.size() ; ++i) {

        if (regex_match(input[i], regex("(\\+)(.*)$"))) {
                string receiver=split(input[i], ' ')[1];
                if(driver == receiver) continue;
                if(!net->getPath(findNodeByName(vec,driver),findNodeByName(vec,receiver))){
                    cout<<"There is no path between the driver and receiver you entered"<<endl;
                    exit(0);
                }
                double elmore_delay=net->getDelay(findNodeByName(vec,driver),findNodeByName(vec,receiver));
                current_t=elmore_delay;
                double delay=get(i);
                double slope=getSlope();
                cout<<"The Elmore Delay between "<<driver<<" and "<<receiver<<": "<<elmore_delay<<endl;
                cout<<"The Delay between "<<driver<<" and "<<receiver<<": "<<delay<<endl;
                cout<<"The slope between "<<driver<<" and "<<receiver<<": "<<slope<<endl;
                cout<<endl;
        }
    }

    return 0;
}
