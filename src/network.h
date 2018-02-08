#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <QFile>
#include <iomanip>
#include <QTime>
#include "node.h"
class Node; // forward declaration


/* reference of the library:
 * https://github.com/meysam81/Sparse-Matrix
 */
#include "../Sparse-Matrix/src/SparseMatrix/SparseMatrix.cpp"

using namespace std;

class Network
{
private:
    Node* nodes;
    int numberOfNodes;

    SparseMatrix<int> *edges;
public:
    Network();
    bool initialize(string inputPath);

    bool computeKShell();

    bool computeNodeInfluence();

    bool computeLabelInfluence();

};


#endif // NETWORK_H
