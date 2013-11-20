/*
 * show.cpp
 *
 *  Created on: 16 lis 2013
 *      Author: vka
 */
#include "show.h"

void show(const System & s)
{
	unsigned widthL = 38;
	unsigned widthR = 38;

	unsigned widthLTop, widthRTop, len = 1, b = s.getTick();
	while((b /= 10) != 0)
		len++;
	widthLTop = widthL - (len + 1) / 2;
	widthRTop = widthR - len / 2;

	std::cout << "| " << std::string(widthLTop, '-') << s.getTick() << std::string(widthRTop, '-') << " |";
	std::cout << std::endl;

	std::cout << "| " << std::left << std::setw(widthL) << "Stan: ";
	std::cout << std::right << std::setw(widthR) << (s.isWorking() ? "pracuje" : "nie pracuje") << " |";
	std::cout << std::endl;

	std::cout << "| " << std::left << std::setw(widthL) << "Kolejek: ";
	std::cout << std::right << std::setw(widthR) << s.numQueues() << " |";
	std::cout << std::endl;

	std::cout << "| " << std::string(widthL + widthR, '-') << " |";
	std::cout << std::endl;

	for(int e = 0; e < s.numQueues(); e++)
	{
		std::stringstream s1, s2;
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
		std::cout << std::left << std::setw(widthL + 2) << s1.str() << std::right << std::setw(widthR + 2) << s2.str();
		std::cout << std::endl;
	}
	std::cout << "| " << std::string(widthL + widthR, '-') << " |" << std::endl << std::endl;
}

