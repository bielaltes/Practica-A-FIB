#ifndef CSVCREATOR_HPP
#define CSVCREATOR_HPP

#include <iostream>
#include <limits>
#include <math.h>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

//static class CSVcreator
class CSVcreator {
	public:
  	static void createCSV();
		
		class	NoFile : public std::exception {
			public:
				virtual const char *	what() const throw();
		};
};

#endif
