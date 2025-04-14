#pragma once
#include "Client.h"

/// Relatie Multi (Cont) la Unul (Client).
class Cont_Bancar
{
	private:
		int ID_Cont;
		int ID_Client;
		double sold;
		char* IBAN;
		char tip_cont; // 'C' = Cont Curent, 'E' = Cont Economii, 'D' = Depozitul
	public:
		Cont_Bancar();
		Cont_Bancar(int, int, double, char*, char);
		~Cont_Bancar();
		inline void Transfer(char*, char*, char*, double);
		void AfisareConturi();

		friend class Client;
};