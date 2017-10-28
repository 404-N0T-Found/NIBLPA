#include "node.h"

void node::addEdge(int i)
{
    if (i == this->label)
        return;
    if (find(connectedTo.begin(), connectedTo.end(), i) != connectedTo.end())
        return;
    connectedTo[i - 1] = i;
    degree++;
}

node::node()
{
    node(0, 0);
}

node::node(int label, int sizeOfNodes)
{
    this->label = label;
    connectedTo = vector<int>(sizeOfNodes, -1);
}

bool node::noEdge()
{
    return connectedTo.size() == 0;
}

bool node::deleteEdge(int i)
{
    connectedTo.erase(connectedTo.begin() + i, connectedTo.begin() + i + 1);
}


ostream &operator <<(ostream &output, const node &n)
{
    for (int i = 0; i < n.connectedTo.size(); i++)
        if (n.connectedTo[i] != -1)
            output << n.label << ":" << n.connectedTo[i] << " ";
    return output;
}
