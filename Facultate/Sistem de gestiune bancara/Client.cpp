#include <iostream>
#include <string>

#include "Client.h"
#include "Angajat.h"

using namespace std;
#pragma warning(disable:4996);

Client::Client()
{
	this->ID_Client = 0;

	this->CNP = new char[2];
	strcpy(this->CNP, "_");

	this->numar_telefon = new char[2];
	strcpy(this->numar_telefon, "_");

	this->nume = new char[2];
	strcpy(this->nume, "_");

	this->prenume = new char[2];
	strcpy(this->prenume, "_");

	this->adresa = new char[2];
	strcpy(this->adresa, "_");
}
Client::Client(int ID_CLIENT, char* NUME, char* PRENUME, char* cnp, char* NUMAR, char* ADRESA)
{
	this->ID_Client = ID_CLIENT;

	this->nume = new char[strlen(NUME) + 1];
	strcpy(this->nume, NUME);

	this->prenume = new char[strlen(PRENUME) + 1];
	strcpy(this->prenume, PRENUME);

	this->CNP = new char[strlen(cnp) + 1];
	strcpy(this->CNP, cnp);

	this->numar_telefon = new char[strlen(NUMAR) + 1];
	strcpy(this->numar_telefon, NUMAR);

	this->adresa = new char[strlen(ADRESA) + 1];
	strcpy(this->adresa, ADRESA);
}

Client::~Client()
{
	delete this->nume;
	delete this->prenume;
	delete this->CNP;
	delete this->numar_telefon;
	delete this->adresa;
}

void Client::Detalii_Cont(Cont_Bancar& CB)
{
	std::cout << "\nDe implementat functia ::Detalii_Cont(Cont_Bancar& CB)!";
}
