/*
 * System.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <vector>
#include <climits> //MAX_INT
#include "Queue.h"
#include "urand.h" //do losowania ilosci nowych klientow
class System
{
public:
	System(void);
	System(unsigned);
	System(const System &);
	~System() {};

	void simulate(bool = true);

	unsigned numQueues(void);
	STATUS getQueueStatus(unsigned);
	unsigned getQueueLength(unsigned);
	unsigned getQueueTime(unsigned);
	void start(void);
	void stop(void);
	bool isWorking(void);
	void setQueueStatus(unsigned, STATUS);//todo private
	unsigned numWorkingQueues(bool = true);
	unsigned numWaitingClients(void);

private:
	std::vector<Queue> queues;
	bool working;
	double _constNewClients;
	double _constRatioToOpenNew;
	double _constRatioToCloseExisting;
	void update(unsigned = 1);
	unsigned chooseBestQueue(void);
	unsigned getRandomQueue(STATUS = CLOSED);
};

#endif /* SYSTEM_H_ */
