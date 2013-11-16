//============================================================================
// Name        : main.cpp
// Author      : vka
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h> //sleep
#include "System.h"
#include "show.h"


using namespace std;

int main() {
	System s(5);

	s.setParams(3, 8, 3, 1);
	s.start();
	int i = 20000;
	while (i--)
	{
		s.simulate();
		show(s);
		//usleep(100000);
		cout << 20000-i<<endl;
	}

	return 0;
}
