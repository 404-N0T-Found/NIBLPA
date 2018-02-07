#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

class node
{
private:
    int label;
    int kShell; // k-shell decomposition value
    int degree = 0; // no edges in the beginning
    int result; // the resulting label after algorithm

public:
    node();
    node(int label);
};


#endif // NODE_H
