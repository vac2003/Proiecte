#pragma once

class Banca
{
	private:
		static int nr_banci;
		char* nume_banca;
		char* locatie_judet;
		char* locatie_oras;
		char* locatie_adresa;
	public:
		Banca();
		Banca(char*, char*, char*, char*);
		Banca(Banca&);
		~Banca();
		void SetNumeBanca(char*);
		void SetLocatieJudet(char*);
		void SetLocatieOras(char*);
		void SetLocatieAdresa(char*);
		char* GetNumeBanca();
		char* GetLocatieJudet();
		char* GetLocatieOras();
		friend char* GetLocatieAdresa(Banca&);
		void AfisareDate();
};
