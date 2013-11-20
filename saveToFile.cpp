/*
 * saveToFile.cpp
 *
 *  Created on: 20 lis 2013
 *      Author: vka
 */

#include "saveToFile.h"

void saveToFile(const System & s, std::ofstream & p)
{
	/*
	 * zapisuje zrzut systemu do pliku
	 * w formacie:
	 * {tick} {ilosc kas} {newClient} {toOpen} {toClose} {posChange} {isWorking: 1-0}
	 * nastepnie dla kazdej kasy (0 - iloscKas - 1) zapisuje linie
	 * {status: 0-3} {iloscKlientow} {czasDoZera}
	 */
	if(!p.is_open())
	{
		std::cerr << "plik nie otwarty" << std::endl;
		return;
	}

	p << s.getTick() << " " << s.numQueues();
	int i = 0;
	while(++i <= 4)
		p << " " << s.getParam(i);
	p << " " << (s.isWorking() ? 1 : 0);

	//zapelnianie kasami

	for(int i = 0; i < s.numQueues(); i++)
		p << std::endl << s.getQueueStatus(i) << " " << s.getQueueLength(i) << " " << s.getQueueTime(i);
}

