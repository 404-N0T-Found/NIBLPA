#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include "node.h"

using namespace std;

class network
{
    friend ostream &operator <<(ostream &, const network&);
private:
    node* testNetwork;
    int numberOfNodes;
public:
    void init();
    network();
};

ostream &operator <<(ostream &output, const network &net);

#endif // NETWORK_H
