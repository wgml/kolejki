/*
 * urand.cpp
 *
 *  Created on: 15 lis 2013
 *      Author: vka
 */

#include "urand.h"

double urand(double start, double end)
{
	boost::uniform_real<> nd(start, end);
	boost::variate_generator<boost::mt19937&,boost::uniform_real<> > var_nor(rng, nd);

	return var_nor();
}
