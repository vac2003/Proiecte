/// Headere default.
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>

/// Header pentru baza de date.
#include <sqlite3.h>

/// Headere pentru banca.
#include "Cont_Bancar.h"
#include "Client.h"
#include "Banca.h"
#include "FunctiiAjutatoare.h"
#include "InterfataMeniuPrincipalLogare.h"
#include "Angajat.h"

/// Headere pentru criptarea datelor.
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#pragma warning(disable:4996)

using namespace std;
using namespace CryptoPP;

// Criptare_Decriptare(reinterpret_cast<const char*>(a));
void Criptare_Decriptare(string plain)
{
    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    //string plain(reinterpret_cast<const char*>(e));
    string cipher, recovered;

    cout << "plain text: " << plain << endl;

    /*********************************\
    \*********************************/

    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource s(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    /*********************************\
    \*********************************/

    cout << "key: ";
    encoder.Put(key, key.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "iv: ";
    encoder.Put(iv, iv.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "cipher text: " << cipher << "      ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl << std::endl;

    /*********************************\
    \*********************************/

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        std::cout << "recovered text: " << recovered << std::endl;
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

int main()
{
	/// Metode de interfata grafica.
	ForteazaConsolaFullscreen();
    ScrieTitluMeniu("~MENIU");

    Client cl(12, (char*)"Gica", (char*)"Petrescu", (char*)"5030203", (char*)"0730", (char*)"jimmy");
    Angajat ang(1, 1, (char*)"test", (char*)"test", (char*)"test", 1);
    ang.Deschide_Cont(cl);

    Cont_Bancar c(9, 9, 3500.24, (char*)"RO04RZBR9474953186696462", 'E');
    c.AfisareConturi();
    //c.Transfer((char*)"test", (char*)"test", (char*)"test", 54.24);
    
    Angajat::AdministrareContClient();
    
    int id_client = MeniuLogare();

    Banca banca((char*)"BRD", (char*)"Prahova", (char*)"Ploiesti", (char*)"Strada Industriala, nr. 98");
    banca.AfisareDate();

    std::cout << "\n";
    std::cout << "\n GetNumeBanca(): " << banca.GetNumeBanca();
    std::cout << "\n GetLocatieJudet(): " << banca.GetLocatieJudet();
    std::cout << "\n GetLocatieOras(): " << banca.GetLocatieOras();
    std::cout << "\n Functie friend GetLocatieAdresa(): " << GetLocatieAdresa(banca);

    getchar();
	return 0;
}