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
#include <cstring> //strcmp
#include "System.h"
#include "show.h"
#include "saveToFile.h"

using namespace std;
using namespace boost::filesystem;

int main(int args, char * argv[]) {

	bool isSub = (args == 2 && strcmp(argv[1], "subprocess") == 0);

	System s(13);
	ofstream * p;
	if(isSub)
		p = new ofstream("data", ios::trunc);
	s.setParams(3, 8, 3, 0.7);
	s.start();
	int i = 1000;
	while (i--)
	{
		if(isSub && exists("break"))
			break;
		if(isSub && (exists("lock") || exists("data")))
		{
			i++;
			continue;
		}
		s.simulate();

		if(isSub)
			saveToFile(s, *p);
		else
			show(s);

		usleep(10000);
	}

	if(isSub)
	{
		p->close();
		delete p;
	}
	return 0;
}
