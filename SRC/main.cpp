#include <iostream>
using namespace std;
#include "../INC/kdtree.hpp"
#include "../INC/CSVcreator.hpp"

int main( int argc, char **argv )
{
    if (argc != 2)
        cerr << "Specify the csv file for reading or create a new one\n";
    else if (string(argv[1]) == "create")
    {
        CSVcreator::createCSV();
    }
    else
    {
        kdtree* k = new kdtree((string(argv[1])));

        //exemple de query per el output.csv
        vector<double> clau = {0.612, 0.489, 0.88};
        node* n = k->get_nearest_neighbor(clau);

        //per veure la clau més propera
        clau = n->getCoords();
        for (int i = 0; i < (int)clau.size(); ++i) cout << clau[i] << ' ';
        cout << endl;
    } 
    return 0;
}
