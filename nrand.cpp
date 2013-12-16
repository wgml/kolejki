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

    double wartosc = nd(rng);

	if(wartosc >= 0)
		return (int) wartosc;
	else
		return (int) (-wartosc);
}
