
#ifndef KDTREE_HPP
# define KDTREE_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include "node.hpp"
#include <fstream>
#include <sstream>


using namespace std;

class kdtree
{
	private:
		int		_size;
        int     _dim;
		node* _root;
		Kd_type _type;
	public:
		//Constructors and destructors
		kdtree();
		kdtree( const string &input );
		kdtree (int sizes, const vector<vector<double>> coords);
		~kdtree( void );
		kdtree(kdtree const &copy);
		kdtree	&operator=(kdtree const &copy);

		//Getters
        int getDim();
		void get_nearest_neighbor_recursive(const vector<double>& query, node* n, node*& nn, double& min_dist, int &total);
		node* get_nearest_neighbor(const vector<double>& query);
		node *get_nearest_neighbor_lineal(const vector<double>& query);
		void get_nearest_neighbor_lineal_recursive(const vector<double>& query, node* n, node*& nn, double& min_dist, int &total);
		//Setters

		//Member functions
		void insert_node(vector<double>& clau);

		class	NoFile : public std::exception
		{
			public:
				virtual const char *	what() const throw();
		};
};

#endif
