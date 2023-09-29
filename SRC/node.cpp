#include "../INC/kdtree.hpp"

node::node( vector<float> &coords, int disc )
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

void node::insert_node(vector<float>& clau) {
    int disc = this->_disc;
    if (clau[disc] < this->_coords[disc]) {
        if (this->_left == nullptr) _left = new node(clau, (disc+1)%this->_coords.size());
        else this->_left->insert_node(clau);
    }
    else if (this->_right == nullptr) _right = new node(clau, (disc+1)%this->_coords.size());
    else this->_right->insert_node(clau);

}
