#pragma once
#include "Persoana.h"
#include "Client.h"
#include "Cont_Bancar.h"

class Angajat : public Persoana
{
	private:
		int ID_Angajat;
		int salariu;
	public:
		Angajat();
		Angajat(int, int, char*, char*, char*, int);
		void Afisare();
		static void AdministrareContClient();
		static int ModificaSold(int);
		static char* ModificaIBAN(int);
		void Deschide_Cont(Client&);
		void Inchide_Cont(Client&);
};