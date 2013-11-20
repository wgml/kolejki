/*
 * saveToFile.h
 *
 *  Created on: 20 lis 2013
 *      Author: vka
 */

#ifndef SAVETOFILE_H_
#define SAVETOFILE_H_

#include <fstream>
#include <iostream> //todo usunac
#include "System.h"

void saveToFile(const System &, std::ofstream &);

#endif /* SAVETOFILE_H_ */
