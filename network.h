#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <node.h>

using namespace std;

class network
{
private:
    node* testNetwork;
    int numberOfNodes;
public:
    void init();
    network();
};

#endif // NETWORK_H
