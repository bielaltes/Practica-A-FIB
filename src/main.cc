#include <iostream>
#include "../inc/kdtree.hh"
#include "../inc/CSVcreator.hh"
#include "../inc/tester.hh"

using namespace std;

typedef vector<vector<double>> matrix;

void usage()
{
    cout << "Usage:" << endl;
    cout << "   test: test on random samples" << endl;
    cout << "   file: execute from an existing file" << endl;
    cout << "   create: create a sample file" << endl;
}


int main(int argc, char **argv)  {
    if (argc != 2) usage();
    else if (string(argv[1]) == "create")
        CSVcreator::createCSV();
    else if (string(argv[1]) == "file") 
        CSVcreator::runCSV();
    else if (string(argv[1]) == "test") 
    {
            int k, n, N, Q; 
            cout << "Inserte el número de dimensiones k: "; cin >> k;
            cout << "Inserte el número de nodos n: ";  cin >> n; 
            cout << "Inserte el número de árboles aleatorios a generar N: "; cin >> N;
            cout << "Inserte el número de consultas a realizar en cada árbol Q: "; cin >> Q;

            tester* t = new tester(k, n, N, Q);
            t->execute();
            t->print_results();
            delete t;
    }
    return 0;
}
