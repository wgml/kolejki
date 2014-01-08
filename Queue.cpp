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

	if(s == OPEN)
		this->status = OPEN;
	else
		this->status = CLOSED;

	this->queue = std::deque<Client>();
}

Queue::Queue(Client c)
{
	this->currentClientTime = 0;
	this->status = OPEN;

	this->queue = std::deque<Client>();
	this->queue.push_back(c);
}

Queue & Queue::operator = (const Queue & q)
{
	this->currentClientTime = q.currentClientTime;
	this->queue = std::deque<Client>(q.queue.begin(), q.queue.end());

	return (*this);
}

unsigned Queue::getLength() const
{
	/*
	 * zwraca ilosc elementow w kolejce
	 */
	if(!this->queue.empty())
		return this->queue.size();
	return 0;
}

unsigned Queue::getTotalTime() const
{
	/*
	 * zwraca calkowity czas (ticki) do wyzerowania kolejki
	 */
	if(this->queue.empty())
		return 0;
	unsigned c = 0;
	for(unsigned i = 0; i < this->getLength(); i++)
		c += this->queue[i].getServiceTime();
	return (c - this->currentClientTime);
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
}

void Queue::setStatus(STATUS s)
{
	this->status = s;
}

void Queue::update(unsigned ticks)
{
	while(ticks > 0 && this->getLength() > 0)
	{
		if(this->getTotalTime() == 0)
			break;//kolejka pusta

		unsigned timeNeeded = this->queue.front().getServiceTime();
		if(ticks + this->currentClientTime < this->queue.front().getServiceTime())
		{
			this->currentClientTime += ticks;
			break;
		}
		else
		{
			ticks -= timeNeeded - currentClientTime;
			this->currentClientTime = 0;
			this->queue.pop_front();
		}

		/*zamyka kolejke, jesli miala sie zamknac
		 * i jest pusta
		 */
		if(this->status == WILL_CLOSE && this->getTotalTime() == 0)
			this->status = CLOSED;
	}
}

Client Queue::removeLast()
{
	/*
	 * usuwa ostatni element z kolejki
	 * i zwraca go
	 */
    if(this->getLength() == 0)
        return Client();
	Client c = this->queue.back();
	this->queue.pop_back();
	return c;
}
