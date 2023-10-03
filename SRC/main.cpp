#include <iostream>
using namespace std;
#include "../INC/kdtree.hpp"
#include "../INC/CSVcreator.hpp"

typedef vector<vector<double>> matrix;

void usage()
{
    cout << "Available commands:" << endl;
    cout << "   create: creates a new sample" << endl;
    cout << "   file: execute from an existing file" << endl;
    cout << "   random: execute random sample" << endl;
}

vector<double> random_point(int dims) {

    vector<double> coords(dims);
    for (int i = 0; i < dims; ++i) {
        coords[i] = ((double) rand()) / RAND_MAX;
    }
    return coords;
}

void execute(kdtree*& k, vector<double>& clau) {
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
    clau = random_point(k->getDim());
    execute(k,clau);
}

void random_trees() {
    int tNum, dims, size, qSize, choice;

    cout << "Type the number of k-d trees to be created: \n";
    cin >> tNum;

    for (int i = 0; i < tNum; ++i) {

        srand(time(NULL));

        cout << "Number of dimensions: \n";
        cin >> dims;

        cout << "Size of sample: \n";
        cin >> size;

        // matriz de doubles, cada fila siendo una posición k-dimensional [0,1]^k

        matrix coords(size, vector<double>());
        for (int j = 0; j < size; ++j) coords[j] = random_point(dims);

        kdtree* k = new kdtree(size, coords);

        cout << "Size of the query: \n";
        cin >> qSize;


        cout << "Randomized (0) or inputed (1) values \n";

        cin >> choice;

        vector<double> clau(dims);

        for (int j = 0; j < qSize; ++j) {
            if (choice == 0) clau = random_point(dims);
            else for (int z = 0; z < dims; ++z) cin >> clau[z];
            execute(k, clau);
        }
    }
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
            random_trees();
        }
        else
            usage();

        
    } 
    return 0;
}
