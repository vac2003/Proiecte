#pragma once
int const IBAN_SIZE = 24;

/// ~~~~~~~~~~~~~~~~~~~~Functii visuale~~~~~~~~~~~~~~~~~~~~
void ForteazaConsolaFullscreen();
void SchimbaFontConsola(int marime_text);
void SchimbaCuloareText(int id_color);
void ScrieTitluMeniu(const char* titlu);
void IesireProgram();

/// ~~~~~~~~~~~~~~~~~~~~Alte functii~~~~~~~~~~~~~~~~~~~~
char* CreareIBAN();
