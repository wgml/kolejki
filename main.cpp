//============================================================================
// Name        : main.cpp
// Author      : vka
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
//#include <cstdlib>
#include <unistd.h> //sleep
#include <boost/filesystem.hpp> //exists()
#include "System.h"
#include "show.h"
#include "saveToFile.h"

using namespace std;
using boost::filesystem;

int main() {

	System s(13);
	ofstream p("data", ios::trunc);
	s.setParams(3, 8, 3, 0.7);
	s.start();
	//saveToFile(s, p);
	int i = 2;
	while (i--)
	{
		if(boost::filesystem::exists("break"))
			break;
		if(boost::filesystem::exists("lock"))
			continue;
		s.simulate();
		saveToFile(s, p);
		usleep(10000);
	}

	p.close();
	return 0;
}
