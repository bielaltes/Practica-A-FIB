#include "../inc/kdtree.hh"

node::node( const vector<double> &coords, int disc) {
    this->_coords = coords;
    this->_disc = disc;
    this->_left = nullptr;
    this->_right = nullptr;
}

node::node(node const & src)  {
    *this = src;
}

node::~node(void) {}

node &	node::operator=(node const & rhs) {
    this->_coords = rhs._coords;
    this->_disc = rhs._disc;
    this->_left = rhs._left;
    this->_right = rhs._right;
	  return *this;
}

int node::getDisc() const {
    return this->_disc;
}

double node::geticoord(int i) const {
    return _coords[i];
}

node* node::getLeftNode() const {
    return this->_left;
}


node* node::getRightNode() const {
    return this->_right;
}

double node::getDistance(const vector<double>& query) const {
    double sum = 0.0;
    for (size_t i = 0; i < _coords.size(); ++i) {
        double diff = _coords[i] - query[i];
        sum += diff*diff;
    }
    return std::sqrt(sum);
}

vector<double> node::getCoords() const {
    return _coords;
}


void node::destroyNodes(node* node) {
    if (node->_left != NULL) {
        destroyNodes(node->_left);
    }
    else delete node->_left;

    if (node->_right != NULL) {
        destroyNodes(node->_right);
    }
    else delete node->_right;

    delete node;
    node = NULL;
}

int node::choose_disc(Kd_type disc_policy, vector<double>& b_box_min, vector<double>& b_box_max) {
    int disc = -1;
    switch(disc_policy) {
        case standard:
            disc = (this->_disc+1)%this->_coords.size();
            break;
        case relaxed:
            disc = rand()%this->_coords.size();
            break;
        case squarish:
            double max = numeric_limits<double>::min();
            for (long unsigned int i = 0; i < b_box_min.size(); ++i) {
                if (b_box_max[i] - b_box_min[i] > max) {
                    max = b_box_max[i] - b_box_min[i];
                    disc = i;
                }
            }
            break;
    }
    return disc;
}

void node::insert_node(const vector<double>& query, Kd_type disc_policy, vector<double>& b_box_min, vector<double>& b_box_max) {
    if (query[this->_disc] < this->_coords[this->_disc]) {
        // Reduzco la caja a partir del discriminante 
        
        b_box_max[this->_disc] = this->_coords[this->_disc]; //bounding_box del cuadrante izquierdo
        if (this->_left == nullptr) {
            int disc = choose_disc(disc_policy,b_box_min, b_box_max);
            _left = new node(query, disc);
        }
        else {
            this->_left->insert_node(query, disc_policy, b_box_min, b_box_max);
        }
    }
    else {
        b_box_min[this->_disc] = this->_coords[this->_disc];
        if (this->_right == nullptr) {
            int disc = choose_disc(disc_policy, b_box_min, b_box_max);
            _right = new node(query, disc);
        }
        else {
            this->_right->insert_node(query, disc_policy, b_box_min, b_box_max);
        }
    }

}
