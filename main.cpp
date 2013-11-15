//============================================================================
// Name        : main.cpp
// Author      : vka
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "System.h"
using namespace std;

void show(System s)
{
	cout << endl << "======" << endl;;
	cout << "Stan: " << ((s.isWorking()) ? "pracuje" : "nie pracuje") << endl;
	cout << "Kolejek: " << s.numQueues() << endl;

		for(int e = 0; e < s.numQueues(); e++)
			if(s.queueStatus(e) == OPEN)
				cout << "Status kolejki #" << e+1 << ": open" << ", oczekuje: " << s.getQueueLength(e) << endl;
			else
				cout << "Status kolejki #" << e+1 << ": closed" << endl;
}
int main() {
	System s(3);

	cout << "Kolejek: " << s.numQueues() << endl;

	show(s);

	s.setQueueStatus(0, OPEN);

	show(s);

	s.simulate();

	show(s);
}
