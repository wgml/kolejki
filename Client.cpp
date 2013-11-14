/*
 * Client.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "Client.h"

Client::Client(void)
{
	/*
	 * tworzy obiekt z losowymi wartosciami
	 */
	this->serviceTime = nrand(10,3);
	this->multiplier = nrand(1,0.3);
}

unsigned Client::getServiceTime(void)
{
	return (unsigned)(*this->serviceTime * this->multiplier);
}


