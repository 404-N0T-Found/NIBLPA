#include "network.h"

Network::Network()
{
    numberOfNodes = 0;
}

bool Network::initialize(string inputPath)
{
    try
    {

        QFile inputFile(QString::fromStdString(inputPath));

        if (!inputFile.open(QFile::ReadOnly)) // try to open the file
            return false;




        // first loop to get the number of nodes
        while (!inputFile.atEnd()) // read until EOF
        {
            QString line = inputFile.readLine(); // read line by line
            line = line.replace('\n', "\0"); // remove the endl

            QStringList list = line.split('\t'); // get two nodes

            int v1 = list.at(0).toInt(),
                    v2 = list.at(1).toInt();

            int value = (v2 > v1 ? v2 : v1);

            if (value > numberOfNodes)
                numberOfNodes = value;
        }


        // now get the edges
        inputFile.seek(0); // put the cursor at the beginning of the file


        // node labels start from zero so we should initializr from 1 to n
        edges = new SparseMatrix<int>(numberOfNodes + 1);

        nodes = new Node[numberOfNodes + 1];
        for (int i = 1; i <= numberOfNodes; ++i)
            nodes[i].label = i;



        // second loop to get the edges
        while (!inputFile.atEnd()) // get number of nodes
        {
            QString line = inputFile.readLine();
            line = line.replace('\n', "\0");


            QStringList list = line.split('\t');


            int v1 = list.at(0).toInt(),
                    v2 = list.at(1).toInt();


            // indirected graph; having edge in both direction
            edges->set(v1, v2, 1);
            edges->set(v2, v1, 1);

            // add the corresponding degree
            nodes[v1].degree++;
            nodes[v2].degree++;

        }

        // close the reading file
        inputFile.close();
    }
    catch(exception e)
    {
        cout << e.what();
    }
}

bool Network::computeKShell()
{
    // to edit the degree
    Node *copyNodes = new Node(*nodes);



    /* to edit (remove) the edges as a process
     * of computing the k-shell decomposition
     */
    SparseMatrix<int> copyEdges = (*edges);



    int currentK = 1;

    bool endLoop;

    do
    {
        endLoop = true;

        bool goToNextK = true;


        for (int cntr = 1; cntr <= numberOfNodes; ++cntr)
        {


#if endLoop == true
            // calculate this function ONCE
            if (nodes[cntr].degree != 0)
                endLoop = false;
#endif


            if (nodes[cntr].degree == currentK)
                if (edges->removeAnEdge(cntr))
                {
                    nodes->degree--;
                    nodes->kShell++;


                    goToNextK = false;
                }
        }


        if (goToNextK)
            currentK++;


    }while (!endLoop);


    // add the nodes with zero k-shell to the minimum shell
    int minKShell = nodes[1].kShell;
    for (int i = 2; i <= numberOfNodes; ++i) // compute the minimum
        if (minKShell > nodes[i].kShell)
            minKShell = nodes[i].kShell;

    for (int i = 1; i <= numberOfNodes; ++i) // assign the minimum
        if (nodes[i].kShell == 0)
            nodes[i].kShell = minKShell;


}
