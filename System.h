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
#include <cmath> //exp
#include "Queue.h"
#include "urand.h" //do losowania ilosci nowych klientow
class System
{
public:
	System(void);
    System(unsigned, unsigned);
	System(const System &);
    //~System() {};

	void simulate(bool = true);

	unsigned numQueues(void) const;
	STATUS getQueueStatus(unsigned) const;
	unsigned getQueueLength(unsigned) const;
	unsigned getQueueTime(unsigned) const;
	void start(void);
	void stop(void);
	bool isWorking(void) const;
	unsigned numWorkingQueues(bool = true) const;
	unsigned numWaitingClients(void) const;
    void setParams(double, double, double, double, double, double, double, unsigned);
	double getParam(int) const;
	unsigned getTick(void) const;
    unsigned getSimulationTime(void) const;

private:
	std::vector<Queue> queues;
	bool working;
	unsigned tick; //ilosc updatow od uruchomienia
    unsigned simulationTime;

	double _constNewClients;
	double _constRatioToOpenNew;
	double _constRatioToCloseExisting;
	double _constPosOfChangingQueue;
    double _constNormalMean;
    double _constNormalSTD;
    double _constSpreadRate;
    unsigned _constRandSeed;

	void update(unsigned = 1);
	unsigned chooseBestQueue(void) const;
	unsigned getRandomQueue(STATUS = CLOSED) const;
	void setQueueStatus(unsigned, STATUS);
};

#endif /* SYSTEM_H_ */
