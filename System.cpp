/*
 * System.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "System.h"

System::System(void)
{
	this->queues.insert(this->queues.begin(), 1, Queue());
}

System::System(unsigned i)
{
	this->queues.insert(this->queues.begin(), i, Queue());
}

System::System(const System & s)
{
	this->queues = s.queues;
}

void System::update(unsigned ticks)
{
	for(std::list<Queue>::iterator it = this->queues.begin(); it != this->queues.end(); it++)
		if((*it).getStatus() == OPEN)
			(*it).update(ticks);
}
