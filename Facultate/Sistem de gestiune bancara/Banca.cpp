#include <iostream>
#include <string>

#include "Banca.h"

using namespace std;
#pragma warning(disable:4996)

int Banca::nr_banci = 0;

Banca::Banca()
{
	this->nume_banca = new char[2];
	strcpy(this->nume_banca, "_");

	this->locatie_judet = new char[2];
	strcpy(this->locatie_judet, "_");

	this->locatie_oras = new char[2];
	strcpy(this->locatie_oras, "_");

	this->locatie_adresa = new char[2];
	strcpy(this->locatie_adresa, "_");

	++nr_banci;
}
Banca::Banca(char* NB, char* LJ, char* LO, char* LA)
{
	this->nume_banca = new char[strlen(NB) + 1];
	strcpy(this->nume_banca, NB);

	this->locatie_judet = new char[strlen(LJ) + 1];
	strcpy(this->locatie_judet, LJ);

	this->locatie_oras = new char[strlen(LO) + 1];
	strcpy(this->locatie_oras, LO);

	this->locatie_adresa = new char[strlen(LA) + 1];
	strcpy(this->locatie_adresa, LA);

	++nr_banci;
}
Banca::Banca(Banca& BANCA)
{
	this->nume_banca = new char[strlen(BANCA.nume_banca) + 1];
	strcpy(this->nume_banca, BANCA.nume_banca);

	this->locatie_judet = new char[strlen(BANCA.locatie_judet) + 1];
	strcpy(this->locatie_judet, BANCA.locatie_judet);

	this->locatie_oras = new char[strlen(BANCA.locatie_oras) + 1];
	strcpy(this->locatie_oras, BANCA.locatie_oras);

	this->locatie_adresa = new char[strlen(BANCA.locatie_adresa) + 1];
	strcpy(this->locatie_adresa, BANCA.locatie_adresa);

	++nr_banci;
}
Banca::~Banca()
{
	delete this->nume_banca;
	delete this->locatie_judet;
	delete this->locatie_oras;
	delete this->locatie_adresa;
}

void Banca::SetNumeBanca(char* NB)
{
	this->nume_banca = new char[strlen(NB) + 1];
	strcpy(this->nume_banca, NB);
}
void Banca::SetLocatieJudet(char* LJ)
{
	this->locatie_judet = new char[strlen(LJ) + 1];
	strcpy(this->locatie_judet, LJ);
}
void Banca::SetLocatieOras(char* LO)
{
	this->locatie_oras = new char[strlen(LO) + 1];
	strcpy(this->locatie_oras, LO);
}
void Banca::SetLocatieAdresa(char* LA)
{
	this->locatie_adresa = new char[strlen(LA) + 1];
	strcpy(this->locatie_adresa, LA);
}

char* Banca::GetNumeBanca() { return this->nume_banca; }
char* Banca::GetLocatieJudet() { return this->locatie_judet; }
char* Banca::GetLocatieOras() { return this->locatie_oras; }
char* GetLocatieAdresa(Banca& B)
{
	return B.locatie_adresa;
}

void Banca::AfisareDate()
{
	cout << "\nDate despre banca: ";
	cout << "\nNumele bancii este: " << this->nume_banca;
	cout << "\nJudetul in care se afla este: " << this->locatie_judet;
	cout << "\nOrasul in care se afla este: " << this->locatie_oras;
	cout << "\nAdresa este: " << this->locatie_adresa;
	cout << "\nNumarul de banci curente este: " << this->nr_banci;
}
