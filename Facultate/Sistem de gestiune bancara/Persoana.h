#pragma once

class Persoana
{
	protected:
		char* nume;
		char* prenume;
		char* CNP;
		int varsta;
	public:
		Persoana();
		Persoana(char*, char*, char*, int);
		Persoana(Persoana&);
		~Persoana();
		void Afisare();
};
