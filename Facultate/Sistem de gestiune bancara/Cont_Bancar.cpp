#include <string>
#include <cassert>
#include <sqlite3.h>
#include <iostream>

#include "Cont_Bancar.h"

#pragma warning(disable:4996)

/// Marimea IBAN-ului international.
int const IBAN_SIZE = 24;

/// Constructori/Destructor
Cont_Bancar::Cont_Bancar()
{
	this->ID_Client = -1;
	this->ID_Cont = -1;
	this->sold = NULL;

	this->IBAN = new char[2];
	strcpy(this->IBAN, "_");
	assert(this->IBAN != 0);

	this->tip_cont = '_';
}
Cont_Bancar::Cont_Bancar(int ID_CONT, int ID_CLIENT, double SOLD, char* iban, char TIP_CONT)
{
	this->ID_Cont = ID_CONT;
	this->ID_Client = ID_CLIENT;
	this->sold = SOLD;
	
	this->IBAN = new char[strlen(iban) + 1];
	strcpy(this->IBAN, iban);
	assert(this->IBAN != 0);

	this->tip_cont = TIP_CONT;
	assert(tip_cont != 0);
}
Cont_Bancar::~Cont_Bancar()
{
	delete this->IBAN;
}

/// Alte functii.
void Cont_Bancar::Transfer(char* nume_beneficiar, char* IBAN, char* detalii, double cantitate_RON)
{
	/// De vazut notita 2 in NOTITE IMPORTANTE.
	/// Functie inutila, face cu totul altceva.

	sqlite3* db;
	sqlite3_stmt* stmt;
	if (sqlite3_open("Banca.db", &db) == SQLITE_OK)
	{
		//int result = sqlite3_prepare_v2(db, "UPDATE Cont_Bancar SET IBAN=? WHERE ID_Client = 1;", -1, &stmt, 0);
		int rezultat = sqlite3_prepare_v2(db, "INSERT INTO Cont_Bancar VALUES(?,?,?,?,?);", -1, &stmt, 0);
		int m = strlen(IBAN);

		sqlite3_bind_int(stmt, 1, this->ID_Cont);
		sqlite3_bind_int(stmt, 2, this->ID_Client);
		sqlite3_bind_double(stmt, 3, this->sold);
		sqlite3_bind_text(stmt, 4, this->IBAN, IBAN_SIZE, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 5, &this->tip_cont, 1, SQLITE_TRANSIENT);

		
		//sqlite3_bind_text(stmt, 1, "testut", m, SQLITE_TRANSIENT);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		if (rezultat != SQLITE_OK)
		{
			std::cout << "ERROR: " << sqlite3_errmsg(db) << "\n";
		}
		else
			std::cout << "Datele au fost adaugate in baza de date cu succes!";

		sqlite3_close(db);
	}

	
}

void Cont_Bancar::AfisareConturi()
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	sqlite3_prepare_v2(db, "SELECT * FROM Cont_Bancar", -1, &stmt, 0);

	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		std::cout << std::endl << sqlite3_column_int(stmt, 0) << " " << sqlite3_column_int(stmt, 1) << " " << sqlite3_column_double(stmt, 2) << " " << sqlite3_column_text(stmt, 3) << " " << sqlite3_column_text(stmt, 4);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
