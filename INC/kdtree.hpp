
#ifndef KDTREE_HPP
# define KDTREE_HPP

#include <iostream>
#include <limits>
#include <math.h>
#include "node.hpp"

using namespace std;

class kdtree
{
	private:
		int		_size;
		node* _root;
        Kd_type _type;
	public:
		//Constructors and destructors
		kdtree( void );
		~kdtree( void );
		kdtree(kdtree const &copy);
		kdtree	&operator=(kdtree const &copy);

		//Getters
		void get_nearest_neighbor_recursive(const vector<double>& query, node* n, node*& nn, double& min_dist);
		node* get_nearest_neighbor(const vector<double>& query);

		//Setters

		//Member functions
	vector<double> random_point(int dims);
    void insert_node(vector<double>& clau);
    void generate_node_and_add(int dims);
    node* random_point_and_nearest_neighbor(int dims);


};

#endif
