/*
 * nrand.h
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#ifndef NRAND_H_
#define NRAND_H_

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <ctime>
//TODO dobry random
unsigned nrand(double mean = 0.0, double dev = 1.0);
static boost::mt19937 rng(1); //TODO sztywny seed
#endif /* NRAND_H_ */
