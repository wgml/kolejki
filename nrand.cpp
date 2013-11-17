/*
 * nrand.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#include "nrand.h"

unsigned nrand(double mean, double dev)
{
	if(nrandQ++ > 10000)
	{
		delete rng;
		rng = new boost::mt19937(2);
		nrandQ = 1;
	}

	boost::normal_distribution<> nd(mean, dev);
	boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > var_nor(*rng, nd);

	double wartosc = var_nor();

	if(wartosc >= 0)
		return (int) wartosc;
	else
		return (int) (-wartosc);
}
