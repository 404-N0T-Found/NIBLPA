#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include "node.h"


/* reference of the library:
 * https://github.com/meysam81/Sparse-Matrix
 */
#include "../../Sparse-Matrix/src/SparseMatrix/SparseMatrix.cpp"

using namespace std;

class network
{
private:
    Node* testNetwork;
    int numberOfNodes;

    SparseMatrix<int> *edges;
public:
    network(string inputFile, string outputFile = "");
    void init();
};


#endif // NETWORK_H
