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
        kdtree k((string(argv[1])));
    } 
    return 0;
}
