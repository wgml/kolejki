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

	unsigned numQueues(void) const;
	STATUS getQueueStatus(unsigned) const;
	unsigned getQueueLength(unsigned) const;
	unsigned getQueueTime(unsigned) const;
	void start(void);
	void stop(void);
	bool isWorking(void) const;
	void setQueueStatus(unsigned, STATUS);//todo private
	unsigned numWorkingQueues(bool = true) const;
	unsigned numWaitingClients(void) const;
	void setParams(double, double, double, double); //todo do testow

private:
	std::vector<Queue> queues;
	bool working;
	double _constNewClients;
	double _constRatioToOpenNew;
	double _constRatioToCloseExisting;
	double _constPosOfChangingQueue;

	void update(unsigned = 1);
	unsigned chooseBestQueue(void) const;
	unsigned getRandomQueue(STATUS = CLOSED) const;
};

#endif /* SYSTEM_H_ */
