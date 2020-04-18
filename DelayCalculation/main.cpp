#include <iostream>
#include "Net.h"


int main() {
    //char* path=argv[0];
    cout << "Please enter the path of the file: ";
    string path;
    cin>>path;
    Net *net = new Net();
    getDelay(net,path);
    delete net;
    return 0;
}
