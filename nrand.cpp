/*
 * nrand.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#include "nrand.h"

boost::mt19937 rng(time(NULL));

unsigned nrand(double mean, double dev, boost::mt19937 gen = rng)
{
	boost::mt19937 rng = gen;
	boost::normal_distribution<> nd(mean, dev);
	boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > var_nor(rng, nd);

	double wartosc = var_nor();

	if(wartosc >= 0)
		return (int) wartosc;
	else
		return (int) (-wartosc);
}
