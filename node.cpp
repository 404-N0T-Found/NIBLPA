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

bool node::noEdge()
{
    return connectedTo.size() == 0;
}


ostream &operator <<(ostream &output, const node &n)
{
    for (int i = 0; i < n.connectedTo.size(); i++)
        output << n.label << ":" << n.connectedTo[i] << " ";
    return output;
}
