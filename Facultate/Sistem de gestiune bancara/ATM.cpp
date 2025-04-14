#include <string>
#include "ATM.h"

using namespace std;

#pragma warning(disable:4996)

/// Constructori/Destructor.
ATM::ATM()
{
	this->ID_ATM = -1;
	this->status = -1;

	this->locatie_judet = new char[2];
	strcpy(this->locatie_judet, "_");

	this->locatie_oras = new char[2];
	strcpy(this->locatie_oras, "_");

	this->locatie_adresa = new char[2];
	strcpy(this->locatie_adresa, "_");

	this->tranzactii_suportate = new char[2];
	strcpy(this->tranzactii_suportate, "_");

	this->suporta_depunere = 0;
}
ATM::ATM(int ID, int STATUS, char* LJ, char* LO, char* LA, char* TS, bool SS)
{
	this->ID_ATM = ID;
	this->status = STATUS;

	this->locatie_judet = new char[strlen(LJ) + 1];
	strcpy(this->locatie_judet, LJ);

	this->locatie_oras = new char[strlen(LO) + 1];
	strcpy(this->locatie_oras, LO);

	this->locatie_adresa = new char[strlen(LA) + 1];
	strcpy(this->locatie_adresa, LA);

	this->tranzactii_suportate = new char[strlen(TS) + 1];
	strcpy(this->tranzactii_suportate, TS);

	this->suporta_depunere = SS;
}
ATM::~ATM()
{
	delete this->locatie_judet;
	delete this->locatie_oras;
	delete this->locatie_adresa;
	delete this->tranzactii_suportate;
}

