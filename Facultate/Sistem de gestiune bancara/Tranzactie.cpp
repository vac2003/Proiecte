#include "Tranzactie.h"
#include <iostream>

Tranzactie::Tranzactie()
{
	this->ID_Tranzactie = 0;
	this->ID_Cont = 0;
	this->cantitate = 0.0;

	data_tranzactie.tm_year = 0;
	data_tranzactie.tm_mon = 0;
	data_tranzactie.tm_mday = 0;
	data_tranzactie.tm_hour = 0;
	data_tranzactie.tm_min = 0;
	data_tranzactie.tm_sec = 0;

	this->tip_tranzactie = -1;
}

Tranzactie::Tranzactie(int ID_TRANZACTIE, int ID_CONT, double CANTITATE, int TIP_TRANZACTIE, tm DT)
{
	this->ID_Tranzactie = ID_TRANZACTIE;
	this->ID_Cont = ID_CONT;
	this->cantitate = CANTITATE;
	this->tip_tranzactie = TIP_TRANZACTIE;

	this->data_tranzactie = DT;
}

void Tranzactie::AfisareTranzactiiCont()
{
	std::cout << "\nDe implementat Tranzactie::AfisareTranzactiiCont()!";
}
