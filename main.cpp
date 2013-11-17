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
#include "urand.h"
#include <cstdlib>
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
		cout << 20000-i<<endl;
		usleep(10000);
	}
	return 0;
}
