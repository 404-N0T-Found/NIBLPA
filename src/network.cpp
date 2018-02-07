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


        }

        // close the reading file
        inputFile.close();
    }
    catch(exception e)
    {
        cout << e.what();
    }
}
