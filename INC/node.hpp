
#ifndef NODE_HPP
# define NODE_HPP

using namespace std;
#include <iostream>
#include <vector>

class node
{
	private:
		vector<double> _coords;
        int         _disc;
        node        *_left;
        node        *_right;
	public:
		//Constructors and destructors
		node(vector<double> &coords, int disc );
		~node( void );
		node(node const &copy);
		node	&operator=(node const &copy);

		//Getters
		int getDisc() const;
		double geticoord(int i) const;
		node* getLeftNode() const;
		node* getRightNode() const;
		double getDistance(const vector<double>& query) const;

		//Setters

		//Member functions

		void destroyNodes(node* node);
    void insert_node(vector<double>& clau);

};

#endif
