#include <iostream>
using namespace std;
#include "../INC/kdtree.hpp"
#include "../INC/CSVcreator.hpp"

void usage()
{
    cout << "Available commands:" << endl;
    cout << "   create: creates a new sample" << endl;
    cout << "   file: execute from an existing file" << endl;
    cout << "   random: execute random sample" << endl;
}

void run_file()
{
    string aux;
    cout << "Insert name of the file" << endl;
    cin >> aux;
    kdtree* k = new kdtree(aux + ".csv");

    cout << "Using random query" << endl;
    //exemple de query per el output.csv
    vector<double> clau(k->getDim());
    srand(time(NULL));
    for (int i = 0; i < k->getDim(); ++i)
    {
        clau[i] = (rand() % 1000000)/1000000.0f ;
    }
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

int main( int argc, char **argv )
{
    if (argc != 2)
        usage();
    else
    {
        if (string(argv[1]) == "create")
        {
            CSVcreator::createCSV();
        }
        else if(string(argv[1]) == "file")
        {
            run_file();
        }
        else if(string(argv[1]) == "random")
        {

        }
        else
            usage();

        
    } 
    return 0;
}
