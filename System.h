/*
 * System.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "Queue.h"
#include <vector>

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
	void setQueueStatus(unsigned, STATUS);
	unsigned numWorkingQueues(void);

private:
	std::vector<Queue> queues;
	bool working;
	double _probOfNewClient;
	void update(unsigned = 1);
	unsigned chooseBestQueue(void);
};


#endif /* SYSTEM_H_ */
