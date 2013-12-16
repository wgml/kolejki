/*
 * Client.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#ifndef KLIENT_H_
#define KLIENT_H_
#include "nrand.h"
class Client
{
public:
	Client(void) : serviceTime(nrand(10, 2)) {};
    Client(int i) : serviceTime(i) {};
	Client(const Client &);
	~Client(void) {};
	unsigned getServiceTime(void) const;
	Client & operator = (const Client &);

private:
	unsigned serviceTime;
    //todo pola statyczne z wartosciami dla generatora
};


#endif /* KLIENT_H_ */
