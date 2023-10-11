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

    random_device RandomDevice;
    unsigned seed = RandomDevice();

    default_random_engine generator(seed);
    uniform_real_distribution<double> Uniforme(0.0, 1.0);
    
    for (int i = 0; i < dim; ++i) 
        coords[i] = Uniforme(generator);
        //coords[i] = ((double) rand()) / RAND_MAX;
    
    return coords;
}

void *tester::exec_pthread(void *aux)
{
    tester *t = (static_cast<pair< tester *, int >*>(aux))->first;
    int ty = (static_cast<pair< tester *, int >*>(aux))->second;
    for (int i = 0; i < t->_N; ++i) {
        Kd_type type;
        if (ty == 0) type = standard;
        else if (ty == 1) type = relaxed;
        else type = squarish;
        kdtree* kdt = new kdtree(t->_n, type);
        for (int i = 0; i < t->_n; ++i) kdt->insert_random_node(t->_k);

        vector<double> query;
        for (int j = 0; j < t->_Q; ++j) {
            query = t->random_point(t->_k);  
            int visited_nodes = 0;
            kdt->get_nearest_neighbor(query, visited_nodes);

            if (ty == 0) t->visited_standard += visited_nodes;
            else if (ty == 1) t->visited_relaxed += visited_nodes;
            else t->visited_squarish += visited_nodes;
        }
        delete kdt;
    }
    return NULL;
}

void tester::execute() {
    pair p1 = make_pair(this, 0);
    pthread_create(&threads[0], NULL, exec_pthread, &p1);
    pair p2 = make_pair(this, 1);
    pthread_create(&threads[1], NULL, exec_pthread, &p2);
    pair p3 = make_pair(this, 2);
    pthread_create(&threads[2], NULL, exec_pthread, &p3);
    
    for (int ty = 0; ty < 3; ++ty) 
            pthread_join(threads[ty], NULL);
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




