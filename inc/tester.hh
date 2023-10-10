#ifndef TESTER_HH
#define TESTER_HH

#include <vector>
#include "kdtree.hh"
#include <random>

typedef vector<double> vd;
typedef vector<vd> vvd;

class tester {
	private:
		int _k; //k-dimensions
		int _n; //n number of nodes
		int _N; //Number of random trees to create
		int _Q; //Number of nearest neighbor in each tree created;
		
		//Deberiamos tener alguna estructura de datos para guardar informacion 
		//sobre cada query de cada árbol (para posteriormente printearlo!)

		int average_standard;
		int average_relaxed;
		int average_squarish;

		double variance_standard;
		double variance_relaxed;
		double variance_squarish;

		vector<double> random_point(int dim);

	public:
		//Constructors and destructors
		tester(int k, int n, int N, int Q);
		~tester(void);

		void execute();
		void print_results();
};


#endif
