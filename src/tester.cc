#include "../inc/tester.hh"

tester::tester(int k, int n, int N, int Q) {
    this->_k = k;
    this->_n = n;
    this->_N = N;
    this->_Q = Q;

    this->average_standard = 0;
    this->average_relaxed = 0;
    this->average_squarish = 0;
}

tester::~tester(void) {}

vd tester::random_point(int dim) {
    vd coords(dim);
    
    random_device RandomDevice;
    unsigned seed = RandomDevice();

    default_random_engine generator(seed);
    uniform_real_distribution<double> Uniforme(0.0, 1.0);

    for (int i = 0; i < dim; ++i) 
        coords[i] = Uniforme(generator);
        //coords[i] = ((double) rand()) / RAND_MAX;
    return coords;
}

void tester::execute() {
    for (int ty = 0; ty < 3; ++ty) { 
        for (int i = 0; i < _N; ++i) {
            Kd_type type;
            if (ty == 0) type = standard;
            else if (ty == 1) type = relaxed;
            else type = squarish;
            kdtree* kdt = new kdtree(_n, _k, type);
            for (int i = 0; i < _n; ++i) kdt->insert_random_node(_k);

        vector<double> query;
        for (int j = 0; j < _Q; ++j) {
            query = random_point(_k);  
            int visited_nodes = 0;
            kdt->get_nearest_neighbor(query, visited_nodes);

                if (ty == 0) average_standard += visited_nodes;
                else if (ty == 1) average_relaxed += visited_nodes;
                else average_squarish += visited_nodes;
            }
            delete kdt;
        }
    }
    average_standard /= (_N*_Q);
    average_relaxed /= (_N*_Q);
    average_squarish /= (_N*_Q);
}

void tester::print_results() {
    cout << endl;
    cout << "---- RESULTS ----" << endl << endl;
    cout << "Standard: " << average_standard << " (average)" << endl;
    cout << "Relaxed: " << average_relaxed << " (average)" << endl;
    cout << "Squarish: " << average_squarish << " (average)" << endl;
}




