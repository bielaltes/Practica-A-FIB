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

void exec_pthread(tester &t, int ty)
{
    for (int i = 0; i < t._N; ++i) {
        Kd_type type;
        if (ty == 0) type = standard;
        else if (ty == 1) type = relaxed;
        else type = squarish;
        kdtree* kdt = new kdtree(t._n, type);
        for (int i = 0; i < t._n; ++i) kdt->insert_random_node(t._k);

        vector<double> query;
        for (int j = 0; j < t._Q; ++j) {
            query = t.random_point(t._k);  
            int visited_nodes = 0;
            kdt->get_nearest_neighbor(query, visited_nodes);

            if (ty == 0) t.visited_standard += visited_nodes;
            else if (ty == 1) t.visited_relaxed += visited_nodes;
            else t.visited_squarish += visited_nodes;
        }
        delete kdt;
    }
}

void tester::execute(tester &t) {
    for (int ty = 0; ty < 3; ++ty) { 
        
    }
    t.visited_standard /= (t._N*t._Q);
    t.visited_relaxed /= (t._N*t._Q);
    t.visited_squarish /= (t._N*t._Q);
}

void tester::print_results() {
    cout << endl;
    cout << "---- RESULTS ----" << endl << endl;
    cout << "Standard: " << visited_standard << " (average)" << endl;
    cout << "Relaxed: " << visited_relaxed << " (average)" << endl;
    cout << "Squarish: " << visited_squarish << " (average)" << endl;
}




