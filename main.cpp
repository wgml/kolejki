//============================================================================
// Name        : main.cpp
// Author      : vka
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h> //sleep
#include <iomanip>
#include <string>
#define ESC char(0x1B)
#include "System.h"

using namespace std;

/*void show(System s)
{
	cout << endl << "======" << endl;;
	cout << "Stan: " << ((s.isWorking()) ? "pracuje" : "nie pracuje") << endl;
	cout << "Kolejek: " << s.numQueues() << endl;

		for(int e = 0; e < s.numQueues(); e++)
			if(s.getQueueStatus(e) == OPEN)
				cout << "Status kolejki #" << e+1 << ": open" << ", oczekuje: " << s.getQueueLength(e)
					<< ", czas: " << s.getQueueTime(e) << endl;
			else
				cout << "Status kolejki #" << e+1 << ": closed" << endl;
}*/

void show(System s)
{
	unsigned widthL = 38;
	unsigned widthR = 38;
	unsigned height = s.numQueues() + 4;

	cout << "| " << std::string(widthL + widthR, '-') << " |";
	cout << endl;

	cout << "| " << std::left << std::setw(widthL) << "Stan: ";
	cout << std::right << std::setw(widthR) << (s.isWorking() ? "pracuje" : "nie pracuje") << " |";
	cout << endl;

	cout << "| " << std::left << std::setw(widthL) << "Kolejek: ";
	cout << std::right << std::setw(widthR) << s.numQueues() << " |";
	cout << endl;

	cout << "| " << std::string(widthL + widthR, '-') << " |";
	cout << endl;

	for(int e = 0; e < s.numQueues(); e++)
	{
		stringstream s1, s2;
		switch(s.getQueueStatus(e))
		{
		case OPEN:
			s1 << "| Kolejka #" << e+1 << ": open";
			s2 << "o: " << s.getQueueLength(e) << ", t: " << s.getQueueTime(e) << " |";
			break;
		case CLOSED:
			s1 << "| Kolejka #" << e+1 << ": closed";
			s2 << "------------ |";
			break;
		case WILL_CLOSE:
			s1 << "| Kolejka #" << e+1 << ": will close";
			s2 << "o: " << s.getQueueLength(e) << ", t: " << s.getQueueTime(e) << " |";
			break;
		}
		cout << std::left << std::setw(widthL + 2) << s1.str() << std::right << std::setw(widthR + 2) << s2.str();
		cout <<endl;
	}
	cout << "| " << std::string(widthL + widthR, '-') << " |" << endl << endl;
}

int main() {
	System s(3);

	s.start();
	s.setQueueStatus(1, OPEN);
	int i = 200;
	while (i--)
	{
		s.simulate();
		show(s);
		usleep(1000000);
	}

	return 0;
}
