/*
 * Client.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "Client.h"

Client::Client(const Client & c)
{
	this->multiplier = c.multiplier;
	this->serviceTime = c.serviceTime;
}

unsigned Client::getServiceTime(void) const
{
	/*
	 * zwraca calkowity czas potrzebny na pozbycie sie z kolejki
	 */
	return ceil(this->serviceTime * this->multiplier);
}

Client & Client::operator = (const Client & c)
{
	this->multiplier = c.multiplier;
	this->serviceTime = c.serviceTime;
	return (*this);
}
