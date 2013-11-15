/*
 * Queue.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

enum STATUS { OPEN, CLOSED, WILL_CLOSE, NO_EXIST};

//TODO Zaokraglanie czasu
#ifndef KOLEJKA_H_
#define KOLEJKA_H_

#include <queue>
#include "Client.h"
class Queue
{
public:
	Queue(void) : totalNeededTime(0), currentClientTime(0), status(CLOSED) {};
	Queue(STATUS s);
	Queue(Client);
	~Queue(void) {};
	Queue & operator = (const Queue &);

	void update(unsigned ticks = 1);
	unsigned getLength(void);
	unsigned getTotalTime(void);
	STATUS getStatus(void);
	void setStatus(STATUS);
	void add(Client);
	bool isEmpty(void);
private:
	std::queue<Client> queue;
	unsigned totalNeededTime;
	unsigned currentClientTime;
	STATUS status;
};


#endif /* KOLEJKA_H_ */
