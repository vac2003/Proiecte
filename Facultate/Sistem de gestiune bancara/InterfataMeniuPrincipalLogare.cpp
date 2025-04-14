#include <iostream>
#include <sqlite3.h>
#include <string>
#include <thread>
#include <chrono>

#include "FunctiiAjutatoare.h"
#include "Client.h"

using namespace std;

/// Returneaza bool, 0 pentru logare fara succes, id_client pentru logare reusita.
int StatusLogare(char* N, char* P)
{
	const unsigned char* numeDB = nullptr, * parolaDB = nullptr;

	char query[200];
	snprintf(query, sizeof query - 1, "SELECT ID_Utilizator, nume_utilizator, parola FROM Utilizator WHERE nume_utilizator = '%s' AND parola = '%s'", N, P);

	int ID_ClientDB = 0;

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	int rezultat = sqlite3_prepare_v2(db, query, sizeof query, &stmt, 0);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}

	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		ID_ClientDB = sqlite3_column_int(stmt, 0);
		numeDB = sqlite3_column_text(stmt, 1);
		parolaDB = sqlite3_column_text(stmt, 2);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return ID_ClientDB;
}
int MeniuLogare()
{
	string nume_utilizator;
	string parola;
	char* N, * P; /// sqlite lucreaza numai in char*, N si P sunt folosite pentru a trece de la string la char* dupa citirea din tastatura.
	int status = 0;

	while (!status)
	{
		system("cls");
		ScrieTitluMeniu("~MENIU PRINCIPAL");

		cout << "Introdu numele: ";
		getline(std::cin, nume_utilizator);

		cout << "Introdu parola: ";
		getline(std::cin, parola);

		N = &nume_utilizator[0];
		P = &parola[0];

		status = StatusLogare(N, P);

		/// status = 1, logare incheita cu succes.
		system("cls");
		if (!status)
		{
			cout << "Datele introduse nu sunt corecte!";
			this_thread::sleep_for(chrono::seconds(1));
		}
		else
		{
			cout << "Bun venit, " << nume_utilizator << "!";
			this_thread::sleep_for(chrono::seconds(1));
		}
	}

	return status;
}

