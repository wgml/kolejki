/*
 * Client.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#ifndef KLIENT_H_
#define KLIENT_H_

class Client
{
public:
	Client(void);
	unsigned getServiceTime(void);

private:
	unsigned serviceTime;
	double multiplier;
};


#endif /* KLIENT_H_ */
