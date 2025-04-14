#pragma once

#include "Client.h"

class Utilizator
{
	private:
		int ID_Utilizator;
		char* nume_utilizator;
		char* parola;
		bool tip_utilizator; /// 0 pentru client, 1 pentru angajat.
	public:
		friend class Client; /// In clasa client este un constructor care afiseaza informatii despre contul de utilizator.
};