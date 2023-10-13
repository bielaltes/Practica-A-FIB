#include "../inc/tester.hh"

tester::tester(int k, int n, int N, int Q) {
    this->_k = k;
    this->_n = n;
    this->_N = N;
    this->_Q = Q;

    this->visited_standard = std::vector<int>();
    this->visited_relaxed = std::vector<int>();
    this->visited_squarish = std::vector<int>();
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

            if (ty == 0) 
            {
                // t->visited_standard += visited_nodes;
                // t->variance_standard += visited_nodes * visited_nodes;
                t->visited_standard.push_back(visited_nodes);
            }
            else if (ty == 1)
            {
                // t->visited_relaxed += visited_nodes;
                // t->variance_relaxed += visited_nodes * visited_nodes;
                t->visited_relaxed.push_back(visited_nodes);
            } 
            else 
                {
                // t->visited_squarish += visited_nodes;
                // t->variance_squarish += visited_nodes * visited_nodes;
                t->visited_squarish.push_back(visited_nodes);
            }
        }
        delete kdt;
    }
    return NULL;
}

void tester::execute() {
    pair<tester*, int> p1 = make_pair(this, 0);
    pthread_create(&threads[0], NULL, exec_pthread, &p1);
    pair<tester*, int> p2 = make_pair(this, 1);
    pthread_create(&threads[1], NULL, exec_pthread, &p2);
    pair<tester*, int> p3 = make_pair(this, 2);
    pthread_create(&threads[2], NULL, exec_pthread, &p3);
    
    for (int ty = 0; ty < 3; ++ty) 
            pthread_join(threads[ty], NULL);
    //visited_standard /= (_N*_Q);
    //visited_relaxed /= (_N*_Q);
    //visited_squarish /= (_N*_Q);
    mean_standard = 0;
    mean_relaxed = 0;
    mean_squarish = 0;
    for (long unsigned int i = 0; i < visited_standard.size(); ++i) {
        mean_standard += visited_standard[i];
        mean_relaxed += visited_relaxed[i];
        mean_squarish += visited_squarish[i];
    }

    mean_standard /= visited_standard.size();
    mean_relaxed /= visited_relaxed.size();
    mean_squarish /= visited_squarish.size();

    for (long unsigned int i = 0; i < visited_standard.size(); ++i) {
        variance_standard += (visited_standard[i] - mean_standard)*(visited_standard[i] - mean_standard); 
        variance_relaxed += (visited_relaxed[i] - mean_relaxed)*(visited_relaxed[i] - mean_relaxed); 
        variance_squarish += (visited_squarish[i] - mean_squarish)*(visited_squarish[i] - mean_squarish); 
    }

    variance_standard /= (visited_standard.size() - 1);
    variance_relaxed /= (visited_relaxed.size() - 1);
    variance_squarish /= (visited_squarish.size() - 1);
    
    //variance_standard = variance_standard/(_N*_Q) - visited_standard;
    //variance_relaxed = variance_relaxed/(_N*_Q) - visited_relaxed;
    //variance_squarish = variance_squarish/(_N*_Q) - visited_squarish;
}

void tester::print_results() {
    cout << endl;
    cout << "---- RESULTS ----" << endl << endl;
    cout << "Standard: Visited nodes: " << mean_standard << " (average) Variança: " << variance_standard << endl;
    cout << "Relaxed: Visited nodes: " << mean_relaxed << " (average) Variança: " << variance_relaxed <<endl;
    cout << "Squarish: Visited nodes: " << mean_squarish << " (average) Variança: " << variance_squarish <<endl;
}




