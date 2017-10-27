#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

class node
{
private:
    int label;
    int kShell;
    int degree = 0;
    int result;
    vector<int> connectedTo;
public:
    void addEdge(int i);
    node();
    node(int label);
};

#endif // NODE_H
