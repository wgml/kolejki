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
	this->working = false;
}

System::System(unsigned i)
{
	this->queues.insert(this->queues.begin(), i, Queue());
	this->working = false;
}

System::System(const System & s)
{
	this->queues = s.queues;
	this->working = s.working;
}

void System::update(unsigned ticks)
{
	for(std::vector<Queue>::iterator it = this->queues.begin(); it != this->queues.end(); it++)
		if((*it).getStatus() == OPEN)
			(*it).update(ticks);
}

unsigned System::numQueues(void)
{
	return this->queues.size();
}

STATUS System::queueStatus(unsigned n)
{
	if(n >= this->queues.size())
		return NO_EXIST;
	else
		return this->queues[n].getStatus();
}

unsigned System::getQueueLength(unsigned q)
{
	if(q >= this->queues.size())
		return 0;
	else
		return this->queues[q].getLength();
}

unsigned System::getQueueTime(unsigned q)
{
	if(q >= this->queues.size())
		return 0;
	else
		return this->queues[q].getTotalTime();
}

bool System::isWorking(void)
{
	return this->working;
}

void System::start(void)
{
	this->working = true;
	this->simulate();
}

void System::stop(void)
{
	this->working = false;
}

void System::simulate(void)
{
	if(!this->working)
		return;
	else
		return;
	//TODO
}
