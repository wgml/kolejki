/*
 * urand.cpp
 *
 *  Created on: 15 lis 2013
 *      Author: vka
 */

#include "urand.h"

double urand(double start, double end)
{
	/*if(urandQ++ > 500)
	{
		srand(time(NULL));
		urandQ = 1;
	}

	return start + (rand() / (1.0 * RAND_MAX)) * (end - start);
*/
	if(urandQ++ > 10000)
	{
		delete rng;
		rng = new boost::mt19937(2);
		urandQ = 1;
	}
	boost::uniform_real<> nd(start, end);
	boost::variate_generator<boost::mt19937&,boost::uniform_real<> > var_nor(*rng, nd);
	return var_nor();
}
