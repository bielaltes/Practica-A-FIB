#include "../inc/CSVcreator.hh"

void CSVcreator::createCSV() {
    string input;
    cout << "Nombre del archivo a crear (sin el .csv): ";
    cin >> input;
    std::ofstream file(input + ".csv");
    if (!file.is_open())
        throw NoFile();

    int dim, size;
    srand(time(NULL));
    cout << "Inserte el número de dimensiones: ";
    cin >> dim;
    cout << "Inserte el número de registros de la muestra: ";
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

void CSVcreator::runCSV()
{
    string aux, aux2;
    Kd_type type;
    cout << "Inserte el nombre del archivo (sin el .csv): ";
    cin >> aux;

    cout << "Escriba el tipo de árbol a usar: standard, relaxed o squarish: ";
    cin >> aux2;

    if (aux2 == "standard") type = standard;
    else if (aux2 == "relaxed") type = relaxed;
    else if (aux2 == "squarish") type = squarish;
    else type = standard;

    kdtree* k = new kdtree(aux + ".csv", type);

    cout << "Usando query aleatoria" << endl << endl;
    //exemple de query per el output.csv
    vector<double> clau(k->getDim());
    srand(time(NULL));
    for (int i = 0; i < k->getDim(); ++i) {
        clau[i] = ((double) rand()) / RAND_MAX;
    }

    static clock_t start;
    cout << "Algoritmo eficiente: \n";
    int visited = 0;
    start = clock();
    node* n = k->get_nearest_neighbor(clau, visited);
    cout << fixed <<"El algoritmo eficiente ha tardado: " << static_cast<double>(clock() - start)/ CLOCKS_PER_SEC << " segundos"<< endl;
    cout << fixed << "En este tiempo ha visitado " << visited << " nodos\n";
    //per veure la clau més propera
    cout << "La query ha estado: ";
    vector<double> v = n->getCoords();
    for (int i = 0; i < (int)clau.size(); ++i) cout << clau[i] << ' ';
    cout << endl;
    cout << "El punto más cercano es ";
    for (int i = 0; i < (int)v.size(); ++i) cout << v[i] << ' ';
    cout << endl << endl;


    /*
    cout << "LINEAL: \n";
    start = clock();
    node* n_lineal = k->get_nearest_neighbor_lineal(clau);
    cout << fixed << "El temps lineal ha tardat: " << static_cast<double>(clock() - start)/ CLOCKS_PER_SEC  << " segons" << endl;

    //per veure la clau més propera
    cout << "La query ha estat: ";
    v = n_lineal->getCoords();
    for (int i = 0; i < (int)clau.size(); ++i) cout << clau[i] << ' ';
    cout << endl;
    cout << "El punt més proper trobat ha estat: ";
    for (int i = 0; i < (int)v.size(); ++i) cout << v[i] << ' ';
    cout << endl << endl;
    */
}


const char *	CSVcreator::NoFile::what() const throw() {
	return ("Problems opening the file");
}
