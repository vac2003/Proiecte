#include <string>
#include <iostream>
#include "Persoana.h"

using namespace std;

#pragma warning(disable:4996)

Persoana::Persoana()
{
	this->nume = new char[2];
	strcpy(this->nume, "_");
	
	this->prenume = new char[2];
	strcpy(this->nume, "_");

	this->CNP = new char[2];
	strcpy(this->nume, "_");

	this->varsta = 0;
}
Persoana::Persoana(char* N, char* P, char* C, int V)
{
	this->nume = new char[strlen(N) + 1];
	strcpy(this->nume, N);

	this->prenume = new char[strlen(P) + 1];
	strcpy(this->prenume, P);

	this->CNP = new char[strlen(C) + 1];
	strcpy(this->CNP, C);

	this->varsta = V;
}
Persoana::Persoana(Persoana& P)
{
	this->nume = new char[strlen(P.nume) + 1];
	strcpy(this->nume, P.nume);

	this->prenume = new char[strlen(P.prenume) + 1];
	strcpy(this->prenume, P.prenume);

	this->CNP = new char[strlen(P.CNP) + 1];
	strcpy(this->CNP, P.CNP);

	this->varsta = P.varsta;
}
Persoana::~Persoana()
{
	delete this->nume;
	delete this->prenume;
	delete this->CNP;
}

void Persoana::Afisare()
{
	cout << "\nAfisare date persoana: ";
	cout << "\nNume: " << this->nume;
	cout << "\nPrenume: " << this->prenume;
	cout << "\nCNP: " << this->CNP;
	cout << "\n Varsta: " << this->varsta;
}
