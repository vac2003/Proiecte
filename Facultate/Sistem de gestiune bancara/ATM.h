#pragma once
#include "Card.h"

/// Relatia Multi (ATM) la Unul (Banca).
class ATM
{
	private:
		int ID_ATM;
		int status; // 0 pentru stricat, 1 pentru in functiune, 2 pentru in reparatie.
		char* locatie_judet;
		char* locatie_oras;
		char* locatie_adresa;
		char* tranzactii_suportate; /// Text cu tranzactii suportate (10 lei, 50 lei etc.) separate prin caracterul ;.
		bool suporta_depunere;
		
	public:
		ATM();
		ATM(int, int, char*, char*, char*, char*, bool);
		~ATM();
		void EliberareNumerar(Card&);
		int InterogareSold(Card&);
};