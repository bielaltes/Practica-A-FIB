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

void kdtree::insert_node(vector<float>& clau) {
    if (_root == nullptr) {
        _root = new node(clau, 0);
    }
    else _root->insert_node(clau);
}
