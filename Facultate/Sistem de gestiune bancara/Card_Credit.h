#pragma once
#include <ctime>
#include "Card.h"

class Card_Credit : public Card
{
	private:
		int limita_cumparare;
		int valoare_rata_lunara;
		tm data_rata;
	public:
		Card_Credit();
		Card_Credit(int, int, tm, int, tm, char*, char*, char*, char*, char*);
		void PlatesteRata();
};