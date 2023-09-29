#include "../INC/kdtree.hpp"

node::node( vector<int> &coords, int disc )
{
    this->_coords = coords;
    this->_disc = disc;
    this->_left = nullptr;
    this->_right = nullptr;
	return ;
}

node::node( node const & src) 
{
    *this = src;
	return;
}

node::~node( void )
{
}

node &	node::operator=( node const & rhs )
{
	this->_coords = rhs._coords;
    this->_disc = rhs._disc;
    this->_left = rhs._left;
    this->_right = rhs._right;
	return *this;
}

void node::destroyNodes(node* node) {
    if (node->_left != NULL) {
        destroyNodes(node->_left);
    }
    else delete node->_left;

    if (node->_right != NULL) {
        destroyNodes(node->_right);
    }
    else delete node->_right;

    delete node;
    node = NULL;
}