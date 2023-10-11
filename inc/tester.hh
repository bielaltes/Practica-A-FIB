#ifndef TESTER_HH
#define TESTER_HH

#include <vector>
#include "kdtree.hh"
#include <pthread.h>

typedef vector<double> vd;
typedef vector<vd> vvd;

class tester {
	public:
		int _k; //k-dimensions
		int _n; //n number of nodes
		int _N; //Number of random trees to create
		int _Q; //Number of nearest neighbor in each tree created;
		
		//Deberiamos tener alguna estructura de datos para guardar informacion 
		//sobre cada query de cada árbol (para posteriormente printearlo!)

		int visited_standard;
		int visited_relaxed;
		int visited_squarish;

        pthread_t threads[3];
		vector<double> random_point(int dim);

	public:
		//Constructors and destructors
		tester(int k, int n, int N, int Q);
		~tester(void);

        static void *exec_pthread(void *t);
		void execute();
		void print_results();
};


#endif
