//============================================================================
// Name        : main.cpp
// Author      : vka
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Queue.h"
#include "Client.h"
using namespace std;

int main() {

	Queue kolejka;
	Client a(2);
	Client b(2);
	kolejka.add(a);
	kolejka.add(b);
	cout << kolejka.getLength() << ":" << kolejka.getTotalTime() << endl;
	while(!kolejka.isEmpty())
	{
		kolejka.update();
		cout << kolejka.getLength() << ":" << kolejka.getTotalTime() << endl;
	}
	return 0;
}
