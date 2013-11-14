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

	void simulate(void);
	void update(unsigned = 1);

	unsigned numQueues(void);
	STATUS queueStatus(unsigned);
	unsigned getQueueLength(unsigned);
	unsigned getQueueTime(unsigned);

private:
	std::vector<Queue> queues;
};


#endif /* SYSTEM_H_ */
