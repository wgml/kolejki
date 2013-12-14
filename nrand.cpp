/*
 * nrand.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */

#include "nrand.h"

unsigned nrand(double mean, double dev)
{
    std::normal_distribution<double> nd(mean, dev);
    //boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > var_nor(rng, nd);

    double wartosc = nd(rng);

	if(wartosc >= 0)
		return (int) wartosc;
	else
		return (int) (-wartosc);
}
