
#ifndef NODE_HPP
# define NODE_HPP

using namespace std;
#include <iostream>
#include <vector>

class node
{
	private:
		vector<int> _coords;
        int         _disc;
        node        *_left;
        node        *_right;
	public:
		//Constructors and destructors
		node( vector<int> &coords, int disc );
		~node( void );
		node(node const &copy);
		node	&operator=(node const &copy);

		//Getters

		//Setters

		//Member functions

};

#endif