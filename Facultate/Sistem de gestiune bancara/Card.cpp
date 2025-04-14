#include <iostream>
#include <ctime>

#include "Card.h"

using namespace std;
#pragma warning(disable:4996)

Card::Card()
{
	this->ID_Client = -1;
	
	this->data_expirare.tm_year = 1900;
	this->data_expirare.tm_mon = 0;

	this->numar_card = new char[2];
	strcpy(this->numar_card, "_");

	this->nume_detinator = new char[2];
	strcpy(this->nume_detinator, "_");

	this->emitent_card = new char[2];
	strcpy(this->emitent_card, "_");

	this->tip_card = new char[2];
	strcpy(this->tip_card, "_");

	this->cod_CVV = new char[2];
	strcpy(this->cod_CVV, "_");
}
Card::Card(int ID, tm DATA_EXPIRARE, char* NC, char* ND, char* EC, char* TC, char* CCV)
{
	this->ID_Client = ID;

	this->data_expirare = DATA_EXPIRARE;

	this->numar_card = new char[strlen(NC) + 1];
	strcpy(this->numar_card, NC);

	this->nume_detinator = new char[strlen(ND) + 1];
	strcpy(this->nume_detinator, ND);

	this->emitent_card = new char[strlen(EC) + 1];
	strcpy(this->emitent_card, EC);

	this->tip_card = new char[strlen(TC) + 1];
	strcpy(this->tip_card, TC);

	this->cod_CVV = new char[strlen(CCV) + 1];
	strcpy(this->cod_CVV, CCV);
}
Card::~Card()
{
	delete this->numar_card;
	delete this->nume_detinator;
	delete this->emitent_card;
	delete this->tip_card;
	delete this->cod_CVV;
}

void Card::Cumparare()
{
	cout << "\nDe programat Card::Cumparare()";
}

void Card::PlatesteFactura()
{
	cout << "\nDe programat Card::PlatesteFactura()";
}

void Card::AfisareIstorieTranzactie()
{
	cout << "\nDe programat Card::AfisareIstorieTranzactie()";

}

