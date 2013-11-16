/*
 * Queue.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "Queue.h"

Queue::Queue(STATUS s)
{
	this->currentClientTime = 0;
	this->totalNeededTime = 0;

	if(s == OPEN)
		this->status = OPEN;
	else
		this->status = CLOSED;
}

Queue::Queue(Client c)
{
	this->currentClientTime = 0;
	this->totalNeededTime = c.getServiceTime();
	this->status = OPEN;
	this->queue.push_back(c);
}

Queue & Queue::operator = (const Queue & q)
{
	this->currentClientTime = q.currentClientTime;
	this->totalNeededTime = q.totalNeededTime;
	this->queue = q.queue;

	return (*this);
}

unsigned Queue::getLength() const
{
	/*
	 * zwraca ilosc elementow w kolejce
	 */
	return this->queue.size();
}

unsigned Queue::getTotalTime() const
{
	/*
	 * zwraca calkowity czas (ticki) do wyzerowania kolejki
	 */
	return this->totalNeededTime;
}

STATUS Queue::getStatus(void) const
{
	return this->status;
}

bool Queue::isEmpty() const
{
	/*
	 * zwraca, czy kolejka jest pusta
	 */
	return this->queue.empty();
}

void Queue::add(Client c)
{
	this->queue.push_back(c);
	this->totalNeededTime += c.getServiceTime();
}

void Queue::setStatus(STATUS s)
{
	this->status = s;
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
			this->queue.pop_front();
		}

		/*zamyka kolejke, jesli miala sie zamknac
		 * i jest pusta
		 */
		if(this->status == WILL_CLOSE && this->totalNeededTime == 0)
			this->status = CLOSED;
	}
}

Client Queue::removeLast()
{
	/*
	 * usuwa ostatni element z kolejki
	 * i zwraca go
	 */
	Client c = this->queue.back();
	this->queue.pop_back();
	return c;
}
