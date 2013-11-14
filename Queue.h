/*
 * Queue.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

//TODO Zaokraglanie czasu
#ifndef KOLEJKA_H_
#define KOLEJKA_H_

#include <queue>
#include "Client.h"
#include <algorithm> //for_each
#include <iostream> //todo wywalic
class Queue
{
public:
	Queue(void) : totalNeededTime(0) {};
	~Queue(void) {};

	void update(unsigned ticks = 1);
	unsigned getLength(void);
	unsigned getTotalTime(void);
	void add(Client);
	bool isEmpty(void);
private:
	std::queue<Client> queue;
	unsigned totalNeededTime;
	unsigned currentClientTime;
};


#endif /* KOLEJKA_H_ */
