# Librarie pentru a sterge ecranul
import os
import colorama

# Librarie folosita pentru culori si stiluri
from colorama import init, Fore, Back, Style
init()

# Clase esentiale
import Interfata
from ClasaCarte import Carte
import ClasaMembruBiblioteca
import ClasaBiblioteca

biblioteca = ClasaBiblioteca.Biblioteca()

print(Style.BRIGHT)

while True:
    os.system('cls')

    Interfata.afisareMeniuPrincipal()
    
    opt = input("\nAlege optiunea dorita: ")
    os.system('cls')

    if opt == "1":
        print(Fore.GREEN + "=-------------------ADAUGA CARTE----------------=")
        nume = input(Fore.LIGHTCYAN_EX + "Insereaza numele cartii: ")
        autor = input("Insereaza autorul cartii: ")
        gen = input("Insereaza genul cartii: ")
        isbn = input("Insereaza ISBN-ul cartii: ")
        carte_adaugata = Carte(nume, autor, gen, isbn)
        biblioteca.adaugaCarte(carte_adaugata)
        
    elif opt == "2":
        print(Fore.GREEN + "=-------------------ELIMINA CARTE----------------=")
        ISBN = input(Fore.LIGHTCYAN_EX + "Insereaza ISBN-ul cartii: ")
        biblioteca.eliminareCarte(ISBN)
        
    elif opt == "3":
        print(Fore.GREEN + "=-------------------IMPRUMUTA CARTE----------------=")
        CNP = input(Fore.LIGHTCYAN_EX + "Insereaza CNP-ul membrului: ")
        isbn = input("Insereaza ISBN-ul cartii imprumutate: ")
        biblioteca.imprumutaCarte(CNP, isbn)

    elif opt == "4":
        print(Fore.GREEN + "=-------------------RETURNEAZA CARTE----------------=")
        CNP = input(Fore.LIGHTCYAN_EX + "Insereaza CNP-ul membrului: ")
        isbn = input(Fore.LIGHTCYAN_EX + "Insereaza ISBN-ul cartii imprumutate: ")
        biblioteca.returCarte(CNP, isbn)

    elif opt == "5":
        print(Fore.GREEN + "=-------------------CAUTA CARTE----------------=")
        nume = input(Fore.LIGHTCYAN_EX + "Insereaza numele cartii: ")
        lista_carti_gasite = biblioteca.cautaCarte(nume)
        for carte in lista_carti_gasite:
            print(carte)
        
    elif opt == "6":
        print(Fore.GREEN + "=-------------------AFISARE CARTI----------------=")
        print(Fore.LIGHTCYAN_EX)
        biblioteca.afiseazaCarti()
        
    elif opt == "7":
        print(Fore.GREEN + "=-------------------AFISARE MEMBRII----------------=")
        print(Fore.LIGHTCYAN_EX)
        biblioteca.afiseazaMembrii()

    elif opt == "8":
        print(Fore.GREEN + "=-------------------AFISARE CARTI IMPRUMUTATE----------------=")
        print(Fore.LIGHTCYAN_EX)
        biblioteca.afiseazaCartiImprumutate()
        
    elif opt == "9":
        backup = input("Creare backup fisiere? (da sau nu): ")
        if backup == "da":
            biblioteca.creareBackup()
            print("Back-up facut cu success!")

        biblioteca.salveazaFisiere()
        raise SystemExit(0)
    
    else:
        print("Optinuea aleasa este invalida!")
    
    input("\nInsereaza orice pentru a continua: ")
        
