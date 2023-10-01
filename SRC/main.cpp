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
        static clock_t start;
        cout << "En temps logaritmic: \n";

        start = clock();
        node* n = k->get_nearest_neighbor(clau);
        cout << fixed <<"El temps logaritmic ha tardat: " << static_cast<double>(clock() - start)/ CLOCKS_PER_SEC << " segons"<< endl;
        //per veure la clau més propera
        clau = n->getCoords();
        for (int i = 0; i < (int)clau.size(); ++i) cout << clau[i] << ' ';
        cout << endl;

        cout << "En temps lineal: \n";
        start = clock();
        node* n_lineal = k->get_nearest_neighbor_lineal(clau);
        cout << fixed << "El temps lineal ha tardat: " << static_cast<double>(clock() - start)/ CLOCKS_PER_SEC  << " segons" << endl;

        //per veure la clau més propera
        clau = n_lineal->getCoords();
        for (int i = 0; i < (int)clau.size(); ++i) cout << clau[i] << ' ';
        cout << endl;
    } 
    return 0;
}
