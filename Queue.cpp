/*
 * Queue.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "Queue.h"

unsigned Queue::getLength()
{
	/*
	 * zwraca ilosc elementow w kolejce
	 */
	return this->queue.size();
}

unsigned Queue::getTotalTime()
{
	/*
	 * zwraca calkowity czas (ticki) do wyzerowania kolejki
	 */
	return this->totalNeededTime;
}

bool Queue::isEmpty()
{
	/*
	 * zwraca, czy kolejka jest pusta
	 */
	return this->queue.empty();
}

void Queue::add(Client c)
{
	this->queue.push(c);
	this->totalNeededTime += c.getServiceTime();
}

void Queue::update(unsigned ticks)
{
	/*unsigned timeNeeded = this->queue.front().getServiceTime();
	if(ticks + this->currentClientTime < timeNeeded)
	{
		this->currentClientTime += ticks;
		this->totalNeededTime -= ticks;
	}

	else
	{

		this->currentClientTime = 0;
		this->totalNeededTime -= ticks;
		std::cout << "usuwanie";
		this->queue.pop();
		this->update(ticks - timeNeeded);
	}*/
	while(ticks > 0)
	{
		if(this->totalNeededTime == 0)
			break;//kolejka pusta

		unsigned timeNeeded = this->queue.front().getServiceTime();
		if(ticks + this->currentClientTime < this->queue.front().getServiceTime())
		{
			this->currentClientTime += ticks;
			this->totalNeededTime -= ticks;
			break;
		}
		else
		{
			this->totalNeededTime -= ticks;
			ticks -= timeNeeded - currentClientTime;
			this->currentClientTime = 0;
			this->queue.pop();
		}
	}
}
