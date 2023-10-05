#ifndef CSVCREATOR_HPP
#define CSVCREATOR_HPP

#include <iostream>
#include <limits>
#include <math.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include "kdtree.hh"
#include "node.hh"

using namespace std;

//static class CSVcreator
class CSVcreator {
	public:
  	    static void createCSV();
        static void runCSV();
		
		class	NoFile : public std::exception {
			public:
				virtual const char *	what() const throw();
		};
};

#endif
