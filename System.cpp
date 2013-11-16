/*
 * System.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "System.h"

System::System(void)
{
	/*
	 * inicjuje sytem z jedna kolejka w stanie zamknietym
	 * i nie pracujacy
	 */
	this->queues.insert(this->queues.begin(), 1, Queue(CLOSED));
	this->working = false;

	this->_constNewClients = 3;
	this->_constRatioToOpenNew = 10;
	this->_constRatioToCloseExisting = 3;
}

System::System(unsigned i)
{
	/*
	 * inicjuje system z i kolejkami
	 * w stanie zamknietym
	 * i nie pracujacy
	 */
	this->queues.insert(this->queues.begin(), i, Queue(CLOSED));
	this->working = false;

	this->_constNewClients = 3;
	this->_constRatioToOpenNew = 10;
	this->_constRatioToCloseExisting = 3;
}

System::System(const System & s)
{
	/*
	 * kopiuje...
	 */
	this->queues = s.queues;
	this->working = s.working;

	this->_constNewClients = s._constNewClients;
	this->_constRatioToOpenNew = s._constRatioToOpenNew;
	this->_constRatioToCloseExisting = s._constRatioToCloseExisting;
}

void System::update(unsigned ticks)
{
	/*
	 * aktualizuje wszystkie dostepne kolejki
	 * o ticks skokow
	 */
	for(std::vector<Queue>::iterator it = this->queues.begin(); it != this->queues.end(); it++)
		if(it->getStatus() == OPEN || it->getStatus() == WILL_CLOSE)
			it->update(ticks);
}

unsigned System::numQueues(void)
{
	/*
	 * zwraca liczbe wszystkich kolejek
	 */
	return this->queues.size();
}

STATUS System::getQueueStatus(unsigned n)
{
	/*
	 * zwraca STATUS status wybranej kolejki
	 */
	if(n >= this->queues.size())
		return NO_EXIST;
	else
		return this->queues[n].getStatus();
}

unsigned System::getQueueLength(unsigned q)
{
	/*
	 * zwraca ilosc czekajacych osob (wlacznie z obslugiwana)
	 * w danej kolejce
	 */
	if(q >= this->queues.size())
		return 0;
	else
		return this->queues[q].getLength();
}

unsigned System::getQueueTime(unsigned q)
{
	/*
	 * zwraca potrzebny czas (ticks) na rozladowanie
	 * kolejki w danym wezle
	 */
	if(q >= this->queues.size())
		return 0;
	else
		return this->queues[q].getTotalTime();
}

bool System::isWorking(void)
{
	/*
	 * zwraca, czy caly system pracuje
	 */
	return this->working;
}

void System::start(void)
{
	/*
	 * opdala system
	 * Nie rownoznaczne z symulacja.
	 */
	this->working = true;
	this->simulate();
}

void System::stop(void)
{
	/*
	 * blokuje system
	 * symulacja nie odpali
	 */
	this->working = false;
}

void System::simulate(bool oneTick)
{
	/*
	 * glowna funkcja
	 * sprawdza, czy system jest w stanie open
	 * jesli tak, do poki stan systemu sie nie zmieni,
	 * przeprowadza symulacje.
	 * Najpierw losuje liczbe nowych klientow,
	 * z prawdopodobienstwem __probOfNewClient.
	 * Nastepnie przydziela ich do dnajkrotszych kolejek.
	 * decyduje, czy nie mozna zamknac nadmiaru kolejek
	 * jesli todo iloscCzekajacych/iloscOtwartychKolejek jest mniejsza od jakiegos consta.
	 * Jesli oneTick == true, wykonuje tylko jeden update i przerywa.
	 * Przydatne by zczytywac dane symulacji na biezaco.
	 * todo http://www.willa.me/2013/11/the-six-most-common-species-of-code.html todo? todo
	 *
	 */
	if(!this->working)
		return;

	while(this->working)
	{
		/*
		 * losowanie lowych klientow
		 */

		unsigned newClients = urand() * this->_constNewClients;
		for(int i = 0; i < newClients; i++)
		{
			unsigned k = this->chooseBestQueue();
			this->queues[k].add(Client(5));//TODO na sztywno
		}

		this->update();

		if((1.0 * this->numWaitingClients()) / this->numWorkingQueues() > this->_constRatioToOpenNew)
		{
			/*
			 * otwieranie nowej kolejki
			 */
			this->setQueueStatus(this->getRandomQueue(), OPEN);
		}
		else if((1.0 * this->numWaitingClients()) / this->numWorkingQueues() < this->_constRatioToCloseExisting)
		{
			/*
			 * przygotowanie do zamkniecia istniejacej kolejki
			 */
			this->setQueueStatus(this->getRandomQueue(OPEN), WILL_CLOSE);
		}

		if(oneTick)
			break;
	}
}

void System::setQueueStatus(unsigned q, STATUS s)
{
	/*
	 * zmienia status kolejki q na dany
	 */
	if(this->queues.size() >= q)
		this->queues[q].setStatus(s);
}

unsigned System::chooseBestQueue(void)
{
	/*
	 * wybiera najlepsza kolejke
	 * ze wszystkich dostepnych (otwartych)
	 */
	unsigned bestValue = UINT_MAX;
	unsigned bestId = 0;
	for(unsigned i = 0; i < this->numQueues(); i++)
		if(this->getQueueStatus(i) == OPEN && this->getQueueLength(i) < bestValue)
		{
			bestId = i;
			bestValue = this->getQueueLength(i);
		}
	return bestId;
}

unsigned System::numWorkingQueues(void)
{
	/*
	 * zlicza pracujace kolejki
	 */
	unsigned counter = 0;
	for(std::vector<Queue>::iterator it = this->queues.begin(); it != this->queues.end(); it++)
		if(it->getStatus() == OPEN || it->getStatus() == WILL_CLOSE)
			counter++;
	return counter;
}

unsigned System::numWaitingClients(void)
{
	/*
	 * zwraca liczbe klientow czekajacych we wszystkich kolejkach
	 */
	unsigned sum = 0;
	for(std::vector<Queue>::iterator i = this->queues.begin(); i != this->queues.end(); i++)
		sum += i->getLength();
	return sum;
}

unsigned System::getRandomQueue(STATUS s)
{
	unsigned r;
	do
		r = ((unsigned) urand(0, this->numQueues())) % this->numQueues();
	while(this->getQueueStatus(r) != s);
	return r;
}
