#include "node.h"

void node::addEdge(int i)
{
    if (i == this->label)
        return;
    connectedTo.push_back(i);
    degree++;
}

node::node() : label(0)
{

}

node::node(int label)
{
    this->label = label;
}

