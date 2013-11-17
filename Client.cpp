/*
 * Client.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "Client.h"

Client::Client(const Client & c)
{
	this->serviceTime = c.serviceTime;
}

unsigned Client::getServiceTime(void) const
{
	/*
	 * zwraca calkowity czas potrzebny na pozbycie sie z kolejki
	 */
	return this->serviceTime;
}

Client & Client::operator = (const Client & c)
{
	this->serviceTime = c.serviceTime;
	return (*this);
}
