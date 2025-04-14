#include <iostream>
#include <sqlite3.h>
#include <string>
#include <thread>
#include <chrono>

#include "Persoana.h"
#include "Angajat.h"
#include "FunctiiAjutatoare.h"

using namespace std;

#pragma warning(disable:4996)

/// Constructori.
Angajat::Angajat() : Persoana()
{
	this->ID_Angajat = -1;
	this->salariu = -1;
}
Angajat::Angajat(int ID_ANGAJAT, int SALARIU, char* NUME, char* PRENUME, char* cnp, int VARSTA) : Persoana(NUME, PRENUME, cnp, VARSTA)
{
	this->ID_Angajat = ID_ANGAJAT;
	this->salariu = SALARIU;
}

void Angajat::Afisare()
{
	Persoana::Afisare();
	cout << "\nDetalii suplimentare angajat: ";
	cout << "\nID: " << this->ID_Angajat;
	cout << "\nSalariu: " << this->salariu;

}

void Angajat::AdministrareContClient()
{
	/// Etapa 1: Se citeste un id de client, daca id-ul se afla in baza de date se trece in etapa 2.
	int ID_Client = 0, rezultat;
	int ID_ClientDB = -1;
	double soldDB = 0.0;
	char* ibanDB = new char[25], * tip_contDB = new char[2];
	cout << "\n\nTastati ID-ul clientului pentru a incepe administrarea contului sau bancar: ";
	cin >> ID_Client;

	string temp = to_string(ID_Client);

	char query[200];
	snprintf(query, sizeof query - 1, "SELECT ID_Client, sold, IBAN, tip_cont FROM Cont_Bancar WHERE ID_Client = '%s'", &temp[0]);

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	rezultat = sqlite3_prepare_v2(db, query, sizeof query, &stmt, 0);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}

	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		ID_ClientDB = sqlite3_column_int(stmt, 0);
		soldDB = sqlite3_column_double(stmt, 1);
		strcpy(ibanDB, (const char*)sqlite3_column_text(stmt, 2));
		strcpy(tip_contDB, (const char*)sqlite3_column_text(stmt, 3));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	/// Etapa 2: Contul Bancar a fost gasit, acum va aparea o interfata cu datele curente al contului si optiuni pentru a le modifica.
	if (ID_Client != ID_ClientDB)
		std::cout << "\nClientul nu se afla in baza de date!";
	else
	{
		int raspuns = 0;
		do
		{
			system("cls");
			ScrieTitluMeniu("~ADMINISTRARE CONT BANCAR");
			cout << "\nDatele curente al contului bancar cu ID-ul " << ID_ClientDB << ":";
			cout << "\nSold: " << soldDB;
			cout << "\nIBAN: " << ibanDB;
			cout << "\nTipul contului: " << tip_contDB;

			cout << "\n\n";
			cout << "1. Modificare sold";
			cout << "\n2. Modificare IBAN";
			cout << "\n0. Iesire.";

			cout << "\n\nAlege optiune: ";
			cin >> raspuns;

			system("cls");
			switch (raspuns)
			{
				case 1:
					soldDB = ModificaSold(ID_ClientDB);
					break;
				case 2:
					strcpy(ibanDB, ModificaIBAN(ID_ClientDB));
					break;
			}
		} while (raspuns);
	}
}

int Angajat::ModificaSold(int ID_CLIENT)
{
	int SOLD = 0;
	cout << "\nScrieti noul sold: ";
	cin >> SOLD;

	int rezultat;
	string temp_id = to_string(ID_CLIENT);
	string temp_sold = to_string(SOLD);

	char query[200];
	snprintf(query, sizeof query - 1, "UPDATE Cont_Bancar SET sold = '%s' WHERE ID_Client = '%s'", &temp_sold[0], &temp_id[0]);

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	rezultat = sqlite3_prepare_v2(db, query, sizeof query, &stmt, 0);
	sqlite3_step(stmt);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}
	else
		std::cout << "\nSoldul a fost modificat cu succes!";

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	this_thread::sleep_for(chrono::seconds(1));
	return SOLD;
}

char* Angajat::ModificaIBAN(int ID_CLIENT)
{
	string IBAN;
	
	while (true)
	{
		cout << "\nScrieti noul IBAN: ";
		cin >> IBAN;
		if (IBAN.length() != 24)
			cout << "\nEROARE! Lungimea IBAN-ului nu este de 24 de caractere!";
		else
			break;
	}

	int rezultat;
	string temp_id = to_string(ID_CLIENT);

	char query[200];
	snprintf(query, sizeof query - 1, "UPDATE Cont_Bancar SET IBAN = '%s' WHERE ID_Client = '%s'", &IBAN[0], &temp_id[0]);

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	rezultat = sqlite3_prepare_v2(db, query, sizeof query, &stmt, 0);
	sqlite3_step(stmt);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}
	else
		std::cout << "\nIBAN-ul a fost modificat cu succes!";

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	this_thread::sleep_for(chrono::seconds(1));

	const int lungime_IBAN = IBAN.length();
	char* iban_return = new char[lungime_IBAN + 1];
	strcpy(iban_return, IBAN.c_str());

	return iban_return;
}

void Angajat::Deschide_Cont(Client& CLIENT)
{
	int ID_Cont_MAX = -1;

	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	/// Preluam cel mai mare id curent in tabelul Cont_Bancar.
	int rezultat = sqlite3_prepare_v2(db, "SELECT MAX(ID_Cont) FROM Cont_Bancar", -1, &stmt, 0);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}

	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		ID_Cont_MAX = sqlite3_column_int(stmt, 0);
	}

	/// Cream contul iar ID_Cont va avea valoarea ID_Cont_MAX + 1.
	rezultat = sqlite3_prepare_v2(db, "INSERT INTO Cont_Bancar VALUES(?,?,?,?,?)", -1, &stmt, 0);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}

	sqlite3_bind_int(stmt, 1, ID_Cont_MAX + 1);
	sqlite3_bind_int(stmt, 2, CLIENT.ID_Client);
	sqlite3_bind_double(stmt, 3, 0.0);
	sqlite3_bind_text(stmt, 4, CreareIBAN(), 24, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, "C", 1, SQLITE_TRANSIENT);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Angajat::Inchide_Cont(Client& CLIENT)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Banca.db", &db);

	/// Pentru a inlocui cu succes %s din query cu id-ul clientului este nevoie sa convertim id-ul din int in string si in parametru adaugam adresa primului caracter din string.
	string temp = to_string(CLIENT.ID_Client);

	char query[200];
	snprintf(query, sizeof query - 1, "DELETE FROM Cont_Bancar WHERE ID_Client = '%s'", &temp[0]);

	/// Preluam cel mai mare id curent in tabelul Cont_Bancar.
	int rezultat = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

	if (rezultat != SQLITE_OK)
	{
		cout << "EROARE: " << sqlite3_errmsg(db) << "\n";
		abort();
	}

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
