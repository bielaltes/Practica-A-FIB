#include <iostream>
using namespace std;
#include "../inc/kdtree.hh"
#include "../inc/CSVcreator.hh"

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

void execute(kdtree*& k, vector<double>& clau, double& timeMedian, int& nodeMedian) {
    static clock_t start;
    cout << "En temps logaritmic: \n";

    start = clock();
    node* n = k->get_nearest_neighbor(clau, nodeMedian);
    cout << fixed <<"El temps logaritmic ha tardat: " << static_cast<double>(clock() - start)/ CLOCKS_PER_SEC << " segons"<< endl;

    timeMedian += static_cast<double>(clock() - start)/ CLOCKS_PER_SEC;

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
    string aux, aux2;
    Kd_type type;
    cout << "Insert name of the file" << endl;
    cin >> aux;

    cout << "Select type of tree: standard, relaxed or squarish: ";
    cin >> aux2;

    if (aux2 == "standard") type = standard;
    else if (aux2 == "relaxed") type = relaxed;
    else if (aux2 == "squarish") type = squarish;
    else type = standard;

    kdtree* k = new kdtree(aux + ".csv", type);


    // Not important for single query executions

    double timeMedian = 0;
    int nodeMedian = 0;

    cout << "Using random query" << endl;
    //exemple de query per el output.csv
    vector<double> clau(k->getDim());
    srand(time(NULL));
    clau = random_point(k->getDim());
    execute(k,clau, timeMedian, nodeMedian);
}

void random_trees() {
    int tNum, dims, size, qSize;

    string aux;

    Kd_type type;

    double timeMedian;
    int nodeMedian;

    cout << "Number of dimensions:\n";
    cin >> dims;

    cout << "Number of nodes:\n";
    cin >> size;

    cout << "Number of k-d trees to be created:\n";
    cin >> tNum;

    cout << "Select type of tree: standard, relaxed or squarish: ";
    cin >> aux;

    if (aux == "standard") type = standard;
    else if (aux == "relaxed") type = relaxed;
    else if (aux == "squarish") type = squarish;
    else type = standard;

    cout << "Number of random queries for each tree:\n";
    cin >> qSize;

    for (int i = 0; i < tNum; ++i) {

        timeMedian = 0.0;
        nodeMedian = 0;

        cout << "Testing for tree " << i << endl;

        srand(time(NULL));

        // matriz de doubles, cada fila siendo una posición k-dimensional [0,1]^k

        matrix coords(size, vector<double>());
        for (int j = 0; j < size; ++j) coords[j] = random_point(dims);

        kdtree* k = new kdtree(size, coords, type);

        vector<double> clau(dims);

        for (int j = 0; j < qSize; ++j) {
            clau = random_point(dims);

            cout << "\n ------------ \n";
            for (int z = 0; z < dims; ++z) cout << clau[z] << " ";
            cout << "\n ------------ \n";
            execute(k, clau, timeMedian, nodeMedian);

            cout << endl;
        }

        cout << "The median of time taken for execution is " << timeMedian / qSize << " seconds " << endl;
        cout << "The median of visited nodes is " << nodeMedian / qSize << endl << endl;
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