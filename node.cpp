#include "node.h"

void node::addEdge(int i)
{
    if (i == this->label || connectedTo[i] == i)
        return;
    connectedTo[i] = i;
    degree++;
}

node::node()
{
    node(0, 0);
}

node::node(int label, int sizeOfNodes)
{
    this->label = label;
    connectedTo = vector<int>(sizeOfNodes + 1, -1);
}

bool node::noEdge()
{
    for (int i = 1; i < connectedTo.size(); i++)
        if (connectedTo[i] > 0)
            return false;
    return true;
}

bool node::deleteEdge(int i)
{
    connectedTo[i] = -1;
}


ostream &operator <<(ostream &output, const node &n)
{
    for (int i = 0; i < n.connectedTo.size(); i++)
        if (n.connectedTo[i] > 0)
            output << n.label << ":" << n.connectedTo[i] << " ";
    return output;
}
