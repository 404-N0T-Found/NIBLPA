#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include "node.h"
#include <QFile>

/* reference of the library:
 * https://github.com/meysam81/Sparse-Matrix
 */
#include "../../Sparse-Matrix/src/SparseMatrix/SparseMatrix.cpp"

using namespace std;

class Network
{
private:
    Node* testNetwork;
    int numberOfNodes;

    SparseMatrix<int> *edges;
public:
    Network();
    bool initialize(string inputPath);
};


#endif // NETWORK_H
