#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

enum Kd_type {standard, relaxed, squarish};

class node {
	private:
		vector<double> _coords;
    int _disc;
    node* _left;
    node* _right;
    int choose_disc(Kd_type disc_policy, vector<double>& b_box_min, vector<double>&b_box_max);

	public:
		//Constructors and destructors
		node(const vector<double> &coords, int disc);
		~node( void );
		node(node const &copy);
		node	&operator=(node const &copy);

		//Getters
		int getDisc() const;
		double geticoord(int i) const;
		node* getLeftNode() const;
		node* getRightNode() const;
		double getDistance(const vector<double>& query) const;
		vector<double> getCoords() const;

		//Setters

		//Member functions
		void destroyNodes(node* node);
        void insert_node(const vector<double>& query, Kd_type disc_policy, vector<double>& b_box_min, vector<double>& b_box_max);
};

#endif
