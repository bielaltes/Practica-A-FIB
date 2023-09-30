#include "../INC/kdtree.hpp"

kdtree::kdtree( void )
{
    this->_size = 0;
    this->_root = nullptr;
	return ;
}

kdtree::kdtree( kdtree const & src) 
{
    *this = src;
	return;
}

kdtree::~kdtree( void )
{
	
	(*this->_root).destroyNodes(this->_root);
	return ;
}

kdtree &	kdtree::operator=( kdtree const & rhs )
{
	this->_size = rhs._size;
    this->_root = rhs._root;
	return *this;
}

//ONE VERSION FOR EACH MEMBER OF THE GROUP :) 

void kdtree::get_nearest_neighbor_recursive(const vector<double>& query, node* n, node* nn, double* min_dist)
{
    if (n == nullptr) return;
    const double dist = n->getDistance(query);

    if (dist < *min_dist) {
        *min_dist = dist;
        nn = n;  
    }

    //j = dicriminant
    int j = n->getDisc();
    
    if (query[j] < n->geticoord(j)) {
        get_nearest_neighbor_recursive(query, n->getLeftNode(), nn, min_dist);
        double diff = fabs(query[j] - n->getDisc());
        if (diff < *min_dist) get_nearest_neighbor_recursive(query, n->getRightNode(), nn, min_dist);
    }
    else {
        get_nearest_neighbor_recursive(query, n->getRightNode(), nn, min_dist);
        double diff = fabs(query[j] - n->getDisc());
        if (diff < *min_dist) get_nearest_neighbor_recursive(query, n->getLeftNode(), nn, min_dist);
    }
}

node* kdtree::get_nearest_neighbor(const vector<double>& query)
{
    double min_dist = numeric_limits<double>::max();
    node* nearest_node = nullptr;

    get_nearest_neighbor_recursive(query, _root, nearest_node, &min_dist);

    return nearest_node;
}


void kdtree::insert_node(vector<double>& clau) {
    if (_root == nullptr) {
        _root = new node(clau, 0);
    }
    else _root->insert_node(clau);
}
