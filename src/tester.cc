#include "../inc/tester.hh"

tester::tester(int k, int n, int N, int Q) {
    this->_k = k;
    this->_n = n;
    this->_N = N;
    this->_Q = Q;

    this->visited_standard = 0;
    this->visited_relaxed = 0;
    this->visited_squarish = 0;
}

tester::~tester(void) {}

vd tester::random_point(int dim) {
    vd coords(dim);
    for (int i = 0; i < dim; ++i) 
        coords[i] = ((double) rand()) / RAND_MAX;
    
    return coords;
}

void tester::execute() {

    for (int ty = 0; ty < 3; ++ty) { 
        for (int i = 0; i < _N; ++i) {
            vvd coords(_n, vector<double>()); 
            for (int j = 0; j < _n; ++j) coords[j] = random_point(_k);
            
            Kd_type type;
            if (ty == 0) type = standard;
            else if (ty == 1) type = relaxed;
            else type = squarish;
            kdtree* kdt = new kdtree(_n, coords, type);
       
            vector<double> query;
            for (int j = 0; j < _Q; ++j) {
                query = random_point(_k);  
                int visited_nodes = 0;
                kdt->get_nearest_neighbor(query, visited_nodes);

                if (ty == 0) visited_standard += visited_nodes;
                else if (ty == 1) visited_relaxed += visited_nodes;
                else visited_squarish += visited_nodes;
            }
        }
    }
    visited_standard /= (_N*_Q);
    visited_relaxed /= (_N*_Q);
    visited_squarish /= (_N*_Q);
}

void tester::print_results() {
    cout << endl;
    cout << "---- RESULTS ----" << endl << endl;
    cout << "Standard: " << visited_standard << " (average)" << endl;
    cout << "Relaxed: " << visited_relaxed << " (average)" << endl;
    cout << "Squarish: " << visited_squarish << " (average)" << endl;
}




