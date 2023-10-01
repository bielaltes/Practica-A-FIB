
#include "../INC/CSVcreator.hpp"

void CSVcreator::createCSV()
{
    string input;
    cout << "Name of the file: \n";
    cin >> input;
    std::ofstream file(input + ".csv");
    if (!file.is_open())
        throw NoFile();

    int dim, size;
    srand(time(NULL));
    cout << "Insert number of dimensions: \n";
    cin >> dim;
    cout << "Insert size of the sample: \n";
    cin >> size;
    file << dim << "," << size << std::endl;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < dim; j++)
        {
            if (j == dim -1)
                file << (rand() % 1000000)/1000000.0f << "\n";
            else
                file << (rand() % 1000000)/1000000.0f << ",";
        }
    }

}


const char *	CSVcreator::NoFile::what() const throw()
{
	return ("Problems opening the file");
}
