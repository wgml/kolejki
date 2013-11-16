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
		if(i%10 == 0)
		{
			show(s);
			cout << 20000-i<<endl;
		}

		//usleep(100000);

	}

	return 0;
}
