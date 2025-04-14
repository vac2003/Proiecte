#include <iostream>
#include "Card_Credit.h"

using namespace std;

Card_Credit::Card_Credit()
{
	this->limita_cumparare = 0;
	this->valoare_rata_lunara = 0;
	this->data_rata.tm_mon = 0;
}
Card_Credit::Card_Credit(int LC, int VR, tm DR, int ID, tm DATA_EXPIRARE, char* NC, char* ND, char* EC, char* TC, char* CCV) : Card(ID, DATA_EXPIRARE, NC, ND, EC, TC, CCV)
{
	this->limita_cumparare = LC;
	this->valoare_rata_lunara = VR;
	this->data_rata = DR;
}

void Card_Credit::PlatesteRata()
{
	cout << "\nDe programat Card_Credit::PlatesteRata()";
}
