#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <stdlib.h>

#include "FunctiiAjutatoare.h"
#pragma warning(disable:4996)

using namespace std;

enum TEXT_COLORS
{
	NONE,
	DARK_BLUE, /// Id = 1
	DARK_GREEN, /// Id = 2
	CYAN, /// Id = 3
	DARK_RED, /// Id = 4
	PURPLE, /// Id = 5
	LIGHT_GREEN, /// Id = 6
	LIGHT_GRAY, /// Id = 7
	GRAY, /// Id = 8
	BLUE, /// Id = 9
	GREEN, /// Id = 10
	LIGHT_BLUE, /// Id = 11
	RED, /// Id = 12
	PINK, /// Id = 13
	YELLOW, /// Id = 14
	WHITE /// Id = 15
};

const char ALFABET_IBAN[36] = { 'A', 'B', 'C', 'D', 'E', 'F',
								'G', 'H', 'I', 'J', 'K', 'L',
								'M', 'N', 'O', 'P', 'Q', 'R',
								'S', 'T', 'U', 'V', 'W', 'X',
								'Y', 'Z', '0', '1', '2', '3',
								'4', '5', '6', '7', '8', '9' };

	/// Forteaza consola sa devina fullscreen. Foloseste libraria windows.h.
void ForteazaConsolaFullscreen()
{
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	int latime_ecran = GetSystemMetrics(SM_CXSCREEN);
	int inaltime_ecran = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(console, latime_ecran * 0.1, inaltime_ecran * 0.1, latime_ecran * 0.9, inaltime_ecran * 0.8, TRUE);
}
/// Schimba marimea si fontul textului.
void SchimbaFontConsola(int marime_text)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = marime_text;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"MS Gothic");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
/// Schimba culoarea textului.
void SchimbaCuloareText(int id_color)
{
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console_color, id_color);
}
/// Iesire din program.
void IesireProgram()
{
	exit(0);
}

char* CreareIBAN()
{
	char* IBAN = new char[25];
	IBAN[0] = 'R';
	IBAN[1] = 'O';
	IBAN[24] = '\0';

	srand(time(NULL));

	for (int i = 2; i <= 23; ++i)
	{
		int index_rand = rand() % 36;
		IBAN[i] = ALFABET_IBAN[index_rand];
	}

	return IBAN;
}

void ScrieTitluMeniu(const char* titlu)
{
	SchimbaFontConsola(24);
	SchimbaCuloareText(10);
	cout << titlu;
	SchimbaFontConsola(20);
	SchimbaCuloareText(14);
}