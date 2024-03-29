/*
 * System.cpp
 *
 *  Created on: 14 lis 2013
 *      Author: vka
 */
#include "System.h"
#include <unistd.h>//todo uzyć czegoś z qt
System::System(void)
{
	/*
	 * inicjuje sytem z jedna kolejka w stanie zamknietym
	 * i nie pracujacy
	 */
	this->queues = std::vector<Queue>();
	this->queues.insert(this->queues.begin(), 1, Queue(CLOSED));
	this->working = false;

	this->_constNewClients = 3;
	this->_constRatioToOpenNew = 10;
	this->_constRatioToCloseExisting = 3;
	this->_constPosOfChangingQueue = 0.7;
    this->_constNormalMean = 10;
    this->_constNormalSTD = 2;
    this->_constSpreadRate = 0.7;
    this->_constRandSeed = 4491232;

	this->tick = 0;
    this->simulationTime = 10000;
}

System::System(unsigned q, unsigned t)
{
	/*
	 * inicjuje system z i kolejkami
	 * w stanie zamknietym
	 * i nie pracujacy
	 */
	this->queues = std::vector<Queue>();
    this->queues.insert(this->queues.begin(), q, Queue(CLOSED));
	this->working = false;

	this->_constNewClients = 3;
	this->_constRatioToOpenNew = 10;
	this->_constRatioToCloseExisting = 3;
	this->_constPosOfChangingQueue = 0.7;
    this->_constNormalMean = 10;
    this->_constNormalSTD = 2;
    this->_constSpreadRate = 0.7;
    this->_constRandSeed = 4491232;

	this->tick = 0;
    this->simulationTime = t;
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
	this->_constPosOfChangingQueue = s._constPosOfChangingQueue;
    this->_constNormalMean = s._constNormalMean;
    this->_constNormalSTD = s._constNormalSTD;
    this->_constSpreadRate = s._constSpreadRate;
	this->tick = s.tick;
    this->simulationTime = s.simulationTime;
    this->_constRandSeed = s._constRandSeed;
}

void System::setParams(double p1, double p2, double p3, double p4, double p5, double p6, double p7, unsigned p8)
{
	/*
	 * ustawia parametry na dane
	 */
	this->_constNewClients = p1;
	this->_constRatioToOpenNew = p2;
	this->_constRatioToCloseExisting = p3;
	this->_constPosOfChangingQueue = p4;
    this->_constNormalMean = p5;
    this->_constNormalSTD = p6;
    this->_constSpreadRate = p7;

    if(this->_constRandSeed != p8)
        rng = std::mt19937(p8);
    this->_constRandSeed = p8;

}

void System::update(unsigned ticks)
{
	/*
	 * aktualizuje wszystkie dostepne kolejki
	 * o ticks skokow
	 */
    while(ticks-- > 0)
    {
        if(this->tick == this->simulationTime)
        {
            this->working = false;
            return;
        }

        for(std::vector<Queue>::iterator it = this->queues.begin(); it != this->queues.end(); it++)
            if(it->getStatus() == OPEN || it->getStatus() == WILL_CLOSE)
                it->update(1);
        this->tick += 1;
    }
}

unsigned System::numQueues(void) const
{
	/*
	 * zwraca liczbe wszystkich kolejek
	 */
	return this->queues.size();
}

STATUS System::getQueueStatus(unsigned n) const
{
	/*
	 * zwraca STATUS status wybranej kolejki
	 */
	if(n >= this->queues.size())
		return NO_EXIST;
	else
		return this->queues[n].getStatus();
}

unsigned System::getQueueLength(unsigned q) const
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

unsigned System::getQueueTime(unsigned q) const
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

bool System::isWorking(void) const
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
     * z prawdopodobienstwem __probOfNewClient * e^... .
	 * Nastepnie przydziela ich do dnajkrotszych kolejek.
	 * decyduje, czy nie mozna zamknac nadmiaru kolejek
	 * jesli iloscCzekajacych/iloscOtwartychKolejek jest mniejsza od jakiegos consta.
	 * W kazdym przejsciu petli pozwala zmienic osobie z dowolnej kolejki miejsce
	 * na miejsce w najkrotszej kolejce z zadanym prawdopodobienstwem.
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
        unsigned newClients = urand() * (this->_constNewClients
            * exp(-0.5*(pow((this->tick - this->simulationTime/2.0)/(_constSpreadRate * this->simulationTime/2.0), 2))));
        for(unsigned i = 0; i < newClients; i++)
		{
			unsigned k = this->chooseBestQueue();
            this->queues[k].add(Client(nrand(this->_constNormalMean, this->_constNormalSTD)));//TODO na sztywno
		}
		this->update();
		/*
		 * zmiana kolejki przez klienta, jesli trzeba
		 * i jesli otwarte jest co najmniej 2 kolejki
		 * i jesli roznica miedzy dlugoscia kolejek to co najmniej 3
		 * index zabezpiecza przed nieskonczona petla,
		 * ogranicza wykonanie do 10 * (1+prawdopodobienstwo przejsc)
		 */
		unsigned indx = 0;
		while(this->numWorkingQueues(false) > 1 && (indx++ < 10 * (1.0 + this->_constPosOfChangingQueue)) && urand() < this->_constPosOfChangingQueue)
		{
			/*
			 * wybiera klienta, ktory spelnia warunki:
			 * ) nie jest obslugiwany
			 * ) nie czeka w najkrotszej kolejce
			 */
			//nie bierze pod uwage odleglosc miedzy kasami przy prawdopodobienstwie
			//losuje kolejke do zmiany
			unsigned num;
			bool toBreak = false;
			unsigned iter = 0;
			do
			{
				num = ((unsigned)urand(0, this->numQueues())) % this->numQueues();
				if(++iter > 1000)
					toBreak = true;
			}
			while(!toBreak && ((this->getQueueLength(num) == 1) || (this->chooseBestQueue() == num) ||
					(this->getQueueStatus(num) == CLOSED) || (this->getQueueStatus(num) == NO_EXIST)));

			//sprawdza, czy roznica dlugosci kolejek jest odpowiednia
			if(this->getQueueLength(num) - this->getQueueLength(this->chooseBestQueue()) < 3)
				continue;

			//sciaga klienta z konca danej kolejki i przenosci go na koniec nakrotszej
			Client c = this->queues[num].removeLast();

			this->queues[this->chooseBestQueue()].add(c);
		}
		if(((1.0 * this->numWaitingClients()) / this->numWorkingQueues() > this->_constRatioToOpenNew)
				&& (this->numWorkingQueues() < this->numQueues()))
		{
			/*
			 * otwieranie nowej kolejki
			 */
			this->setQueueStatus(this->getRandomQueue(), OPEN);
		}

		else if(((1.0 * this->numWaitingClients()) / this->numWorkingQueues(false) < this->_constRatioToCloseExisting) && this->numWorkingQueues(false) > 1)
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

unsigned System::chooseBestQueue(void) const
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

unsigned System::numWorkingQueues(bool withWillClose) const
{
	/*
	 * zlicza pracujace kolejki (Status = OPEN || WILL_CLOSE)
	 * lub tylko otwarte, jesli arg = true;
	 */
	unsigned counter = 0;
	for(unsigned i = 0; i < this->numQueues(); i++)
		if(this->queues[i].getStatus() == OPEN || (withWillClose && this->queues[i].getStatus() == WILL_CLOSE))
			counter++;
	return counter;
}

unsigned System::numWaitingClients(void) const
{
	/*
	 * zwraca liczbe klientow czekajacych we wszystkich kolejkach
	 */
	unsigned sum = 0;
	for(unsigned i = 0; i < this->numQueues(); i++)
		sum += this->queues[i].getLength();
	return sum;
}

unsigned System::getRandomQueue(STATUS s) const
{
	unsigned r;
	do
		r = ((unsigned) urand(0, this->numQueues())) % this->numQueues();
	while(this->getQueueStatus(r) != s);
	return r;
}

unsigned System::getTick(void) const
{
	return this->tick;
}

double System::getParam(int p) const
{
	/*
	 * zwraca wartosc danego param
	 * w kolejnosci (1-...)!!:
	 * double _constNewClients;
	 * double _constRatioToOpenNew;
	 * double _constRatioToCloseExisting;
	 * double _constPosOfChangingQueue;
	 * lub zero, jesli poza zakresem
	 */
	switch(p)
	{
	case 1:
		return this->_constNewClients;
	case 2:
		return this->_constRatioToOpenNew;
	case 3:
		return this->_constRatioToCloseExisting;
	case 4:
		return this->_constPosOfChangingQueue;
    case 5:
        return this->_constNormalMean;
    case 6:
        return this->_constNormalSTD;
    case 7:
        return this->_constSpreadRate;
    case 8:
        return this->_constRandSeed;
	default:
		return 0;
	}
}

unsigned System::getSimulationTime(void) const
{
    return this->simulationTime;
}

unsigned System::getCurrentTIck() const
{
    return this->tick;
}
