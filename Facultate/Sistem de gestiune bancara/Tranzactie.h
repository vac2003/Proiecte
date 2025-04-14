#pragma once
#include <ctime>

/// De gandit, probabil ca relatia sa fie Unul (Cont) la Multi (Tranzactii)
class Tranzactie
{
	private:
		int ID_Tranzactie;
		int ID_Cont;
		double cantitate;
		int tip_tranzactie; // 0 = Eliberare, 1 = Depunere, 2 = Transfer.
		tm data_tranzactie;
	public:
		Tranzactie();
		Tranzactie(int, int, double, int, tm);
		void AfisareTranzactiiCont();
};