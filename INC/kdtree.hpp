
#ifndef KDTREE_HPP
# define KDTREE_HPP

#include <iostream>
#include "node.hpp"

class kdtree
{
	private:
		int		_size;
		node	*_root;
	public:
		//Constructors and destructors
		kdtree( void );
		~kdtree( void );
		kdtree(kdtree const &copy);
		kdtree	&operator=(kdtree const &copy);

		//Getters

		//Setters

		//Member functions

};

#endif