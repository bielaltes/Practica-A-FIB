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
    //this should delete all nodes performing a path
	return ;
}

kdtree &	kdtree::operator=( kdtree const & rhs )
{
	this->_size = rhs._size;
    this->_root = rhs._root;
	return *this;
}