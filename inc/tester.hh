#ifndef TESTER_HH
#define TESTER_HH

#include <vector>
#include "kdtree.hh"
#include <pthread.h>

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

		double mean_standard = 0;
		double mean_relaxed = 0;
		double mean_squarish = 0;

        double variance_standard = 0;
        double variance_relaxed = 0;
        double variance_squarish = 0;

        std::vector<int> visited_standard;
        std::vector<int> visited_relaxed;
        std::vector<int> visited_squarish;

        pthread_t threads[3];
		

	public:
		//Constructors and destructors
		tester(int k, int n, int N, int Q);
		~tester(void);

        int getn(){return _n;}
        int getN(){return _N;}
        int getk(){return _k;}
        int getQ(){return _Q;}
        vector<int> &getvisited_standard(){return visited_standard;}
        vector<int> &getvisited_relaxed(){return visited_relaxed;}
        vector<int> &getvisited_squarish(){return visited_squarish;}
        vector<double> random_point(int dim);
        static void *exec_pthread(void *t);
		void execute();
		void print_results();
};


#endif
