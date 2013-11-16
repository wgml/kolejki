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

	s.setParams(2, 8, 6);
	s.start();
	int i = 200;
	while (i--)
	{
		s.simulate();
		show(s);
		usleep(1000000);
	}

	return 0;
}
