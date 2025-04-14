#pragma once
#include <ctime>

/// De verificat daca pot deriva din clasa asta card credit/debit.
/// Relatie Multi (Card) la Unul (Client).
class Card
{
	private:
		int ID_Client;
		tm data_expirare;
		char* numar_card;
		char* nume_detinator;
		char* emitent_card;
		char* tip_card; // Mastercard/Visa etc.
		char* cod_CVV;
	public:
		Card();
		Card(int, tm, char*, char*, char*, char*, char*);
		~Card();
		void Cumparare();
		void PlatesteFactura();
		void AfisareIstorieTranzactie(); // De vazut in Tranzactii.h
};