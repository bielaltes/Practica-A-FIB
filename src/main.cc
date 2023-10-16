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
    if (argc != 2 && argc != 6) usage();
    else if (string(argv[1]) == "create")
        CSVcreator::createCSV();
    else if (string(argv[1]) == "file") 
        CSVcreator::runCSV();
    else if (string(argv[1]) == "test" && argc == 6) 
    {
            int k, n, N, Q; 
            /*cout << "Insert the number of dimensions k: "; cin >> k;
            cout << "Insert the number of nodes n: ";  cin >> n; 
            cout << "Insert the number of random trees to generate: "; cin >> N;
            cout << "Insert the number of queries in each tree: "; cin >> Q;
            */
            k = atoi(argv[2]);
            n = atoi(argv[3]);
            N = atoi(argv[4]);
            Q = atoi(argv[5]);
            tester* t = new tester(k, n, N, Q);
            t->execute();
            t->print_results();
            delete t;
    }
    return 0;
}
