/*
 * Client.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#ifndef KLIENT_H_
#define KLIENT_H_
#include "nrand.h"
#include <cmath> //ceil
#include <iostream>
class Client
{
public:
	Client(void) : serviceTime(nrand(10, 3)), multiplier(nrand(1, 0.3)) {};
	Client(int i) : serviceTime(i), multiplier(1) {};//TODO do testow
	Client(const Client &);
	~Client(void) {};
	unsigned getServiceTime(void);
	Client & operator = (const Client &);

private:
	unsigned serviceTime;
	double multiplier;
};


#endif /* KLIENT_H_ */
