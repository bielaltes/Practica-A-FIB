#include "../INC/kdtree.hpp"

kdtree::kdtree() {
    _size = 0;
    _dim = 0;
    _root = nullptr;
    _type = standard;
}  

kdtree::kdtree( const string &input )
{
    this->_size = 0;
    this->_root = nullptr;
    this->_type = standard;

    std::ifstream file(input);
    if (!file.is_open())
        throw NoFile();

    string line;
    getline(file, line);
    stringstream ss(line);
    
    char aux;
    ss >> _dim >> aux >> _size;

    cout << "Dimensions: " << _dim << " " << "Number of points " << _size << endl;

    for (int i = 0; i < _size; ++i) 
    {
        std::string line;
        if (std::getline(file, line)) 
        {
            std::istringstream lineStream(line);
            string aux;
            std::vector<double> values;
            for (int j = 0; j < _dim; ++j)
            {
                getline(lineStream, aux, ',');
                values.push_back(atof(aux.c_str()));
            }
            insert_node(values);
        }
    }

	return ;
}

kdtree::kdtree(int size, vector<vector<double>> coords) {
    this->_size = 0;
    this->_root = nullptr;
    this->_type = standard;

    for (int i = 0; i < size; ++i) insert_node(coords[i]);
}

kdtree::kdtree( kdtree const & src) 
{
    *this = src;
	return;
}

kdtree::~kdtree( void )
{
    if (this->_root == nullptr) delete this->_root;
    else (*this->_root).destroyNodes(this->_root);
    return;
}

kdtree &	kdtree::operator=( kdtree const & rhs )
{
	this->_size = rhs._size;
    this->_root = rhs._root;
	return *this;
}

int kdtree::getDim()
{
    return (this->_dim);
}


void kdtree::get_nearest_neighbor_recursive(const vector<double>& query, node* n, node*& nn, double& min_dist, int &total)
{
    if (n == nullptr) return;
    const double dist = n->getDistance(query);
    //cout << "visiting node with 0-dim coord: " << n->geticoord(0) << endl;
    //cout << "Euclidian distance: " << dist << endl << endl;

    if (dist < min_dist) {
        min_dist = dist;
        nn = n;  
    }

    //j = dicriminant
    int j = n->getDisc();
    total++;
    if (query[j] < n->geticoord(j)) {
        get_nearest_neighbor_recursive(query, n->getLeftNode(), nn, min_dist, total);
        double diff = abs(query[j] - n->geticoord(j));
        if (diff < min_dist) get_nearest_neighbor_recursive(query, n->getRightNode(), nn, min_dist, total);
    }
    else {
        get_nearest_neighbor_recursive(query, n->getRightNode(), nn, min_dist, total);
        double diff = abs(query[j] - n->geticoord(j));
        if (diff < min_dist) get_nearest_neighbor_recursive(query, n->getLeftNode(), nn, min_dist, total);
    }
}

node* kdtree::get_nearest_neighbor(const vector<double>& query, int& retNodes)
{
    double min_dist = numeric_limits<double>::max();
    node* nearest_node = nullptr;
    int total = 0;
    get_nearest_neighbor_recursive(query, _root, nearest_node, min_dist, total);
    cout << "Nodes visitats: " << total << endl;

    retNodes += total;

    return nearest_node;
}

void kdtree::get_nearest_neighbor_lineal_recursive(const vector<double>& query, node* n, node*& nn, double& min_dist, int &total)
{
    if (n == nullptr) return;
    const double dist = n->getDistance(query);

    if (dist < min_dist) {
        min_dist = dist;
        nn = n;  
    }
    total++;
    get_nearest_neighbor_lineal_recursive(query, n->getRightNode(), nn, min_dist, total);
    get_nearest_neighbor_lineal_recursive(query, n->getLeftNode(), nn, min_dist, total);
}


node* kdtree::get_nearest_neighbor_lineal(const vector<double>& query)
{
    double min_dist = numeric_limits<double>::max();
    node* nearest_node = nullptr;
    int total = 0;
    get_nearest_neighbor_lineal_recursive(query, _root, nearest_node, min_dist, total);
    cout << "Nodes visitats: " << total << endl;
    return nearest_node;

}




void kdtree::insert_node(vector<double>& clau) {
    if (_root == nullptr) {
        _root = new node(clau, 0);
    }
    else{
        vector<double> vd(clau.size(), 1.0);
        _root->insert_node(clau, _type, vd);
    }
}

const char *	kdtree::NoFile::what() const throw()
{
	return ("Problems reading the file");
}
