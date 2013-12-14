/*
 * urand.cpp
 *
 *  Created on: 15 lis 2013
 *      Author: vka
 */

#include "urand.h"
double urand(double start, double end)
{
    std::uniform_real_distribution<> ud(start, end);
    return ud(rng);
}
