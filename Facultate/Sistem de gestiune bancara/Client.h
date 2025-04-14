#pragma once

#include "Cont_Bancar.h"
#include "Persoana.h"

class Client
{
public:
	int ID_Client;
	char* nume;
	char* prenume;
	char* CNP;
	char* numar_telefon;
	char* adresa;
public:
	Client();
	Client(int, char*, char*, char*, char*, char*);
	~Client();
	void Detalii_Cont(class Cont_Bancar&);
};
