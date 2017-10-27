#include "network.h"

void network::init()
{
    cout << "Enter number of network nodes: ";
    cin >> numberOfNodes;
    testNetwork = new node[numberOfNodes + 1];
    cout << "Enter node labels each node is connected to; Zero if none.\n";
    for (int i = 1; i <= numberOfNodes; i++)
    {
        testNetwork[i] = node(i);
        cout << i << ". ";
        string temp;
        if (i == 1)
            getline(cin, temp);
        getline(cin, temp);
        string delimiter = " ";
        size_t pos = 0;
        while ((pos = temp.find(delimiter)) != string::npos)
        {
            string tmp = temp.substr(0, pos);
            try
            {
                int tmpNum = atoi(tmp.c_str());
                if (tmpNum >= 1 && tmpNum <= numberOfNodes)
                    testNetwork[i].addEdge(tmpNum);
            }
            catch(exception e)
            {
                cout << e.what();
            }
            temp.erase(0, pos + delimiter.length());
        }
    }
}

network::network()
{

}