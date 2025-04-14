from ClasaCarte import Carte
from ClasaMembruBiblioteca import Membru

class Biblioteca(object):
    def __init__(self):
        fis_carti = open("carti.txt", "r")
        self.carti = [] # Toate datele despre cartile care apartin
        fis_membrii = open("membrii.txt", "r")
        self.membrii = [] # Toate datele despre membrii bibliotecii

        # Citeste cartile din fisierul 'carti.txt'
        for date_carte in fis_carti.readlines():
            date_sep = date_carte.split(';')
            
            carte = Carte(date_sep[0], date_sep[1], date_sep[2], date_sep[3])
            
            if date_sep[4].lower().strip() == 'da':
                carte.imprumutat = True
            
            self.carti.append(carte)
            
        # Citeste membrii din fisierul 'membrii.txt'
        for date_membru in fis_membrii.readlines():
            date_sep = date_membru.split(';')
            lista_carti_imprumutate = []

            for i in range(4, len(date_sep)):
                carte_gasita = next((carte for carte in self.carti if carte.isbn in date_sep[i]), None)
                lista_carti_imprumutate.append(carte_gasita)
            
            membru = Membru(date_sep[0], date_sep[1], date_sep[2], date_sep[3])
            membru.carti_imprumutate = lista_carti_imprumutate
            self.membrii.append(membru)

        fis_carti.close()
        fis_membrii.close()

        
    def adaugaCarte(self, carte):
        self.carti.append(carte)
        print(f'A fost adaugata o noua carte in biblioteca:\n {carte}') # {carte} = initalizata functia __str_ din clasa ClasaCarte = afisare date despre carte
        
    def eliminareCarte(self, isbn): # Pot exista mai multe carti cu acelasi nume asa ca se va folosi identificatorul unic ISBN pentru a elimina permanent o carte din biblioteca
        # Folosind functia next, iteratia se va opri in momentul in care s-a gasit cartea cu isbn-ul dorit
        # De asemenea daca nu s-a gasit cartea dorita, next() va returna valoarea 'default' si anume None.
        carte_gasita = next((carte for carte in self.carti if carte.isbn == isbn), None) 
        if carte_gasita is not None:
            self.carti.remove(carte_gasita)
            print(f'Urmatoarea carte a fost eliminata din baza de date: \n{carte_gasita}')
        else:
            print(f'Cartea cu ISBN-ul {isbn} NU a fost gasita!')
            
    def imprumutaCarte(self, membru_CNP, isbn): #membru = obiect de tip clasa Membru (ClasaMembruBiblioteca.py)
        membru = next((mem for mem in self.membrii if mem.CNP.strip() == membru_CNP), None)
        carte_imprumutata = next((carte for carte in self.carti if carte.isbn.strip() == isbn), None)
        
        if membru is not None and carte_imprumutata is not None:
            membru.imprumutaCarte(carte_imprumutata)
        else:
            print(f'Cartea sau membrul NU a fost gasit/a in baza de date!')
            
    def returCarte(self, membru_CNP, isbn):
        membru = next((mem for mem in self.membrii if mem.CNP == membru_CNP), None)
        carte_returnata = next((carte for carte in self.carti if carte.isbn == isbn), None)
        if membru is not None and carte_returnata is not None:
            membru.returCarte(carte_returnata)
        else:
            print(f'Cartea sau membrul NU a fost gasit/a in baza de date!')
            
    # Returneaza o lista cu carti care care contin in numele lor valoarea lui 'carte_nume'.
    def cautaCarte(self, carte_nume):
        return [carte for carte in self.carti if carte_nume.lower() in carte.nume.lower()]
    
    # Afiseaza toate cartile din baza de date a bibliotecii.
    def afiseazaCarti(self):
        for carte in self.carti:
            print(carte)
            
    def afiseazaCartiImprumutate(self):
        for carte_impr in self.carti:
            if carte_impr.imprumutat is True:
                print(carte_impr)
        
    def afiseazaMembrii(self):
        for mem in self.membrii:
            print(mem)
            
    def creareBackup(self):
        # Cream un back-up la fisiere
        with open("carti.txt", "r") as foriginal, open("carti_backup.txt", "w") as fbackup:
            for linie in foriginal:
                fbackup.write(linie)
                
        with open("membrii.txt", "r") as foriginal, open("membrii_backup.txt", "w") as fbackup:
            for linie in foriginal:
                fbackup.write(linie)

    def salveazaFisiere(self):
                

        # Se salveaza informatiile noi in fisiere
        with open("carti.txt", "w") as foriginal:
            for carte in self.carti:
                impr = "DA" if carte.imprumutat is True else "NU"
                
                foriginal.write(carte.nume + ";" + carte.autor + ";" + carte.gen + ";" + carte.isbn + ";" + impr + "\n")
                
        with open("membrii.txt", "w") as foriginal:
            for mem in self.membrii:
                carti_imprum = ""
                for carte in mem.carti_imprumutate:
                    carti_imprum = carti_imprum + carte.isbn + ";"

                if mem.carti_imprumutate != []:
                    foriginal.write(mem.nume + ";" + mem.prenume + ";" + mem.varsta + ";" + mem.CNP.strip() + ";" + carti_imprum[:-1].strip() + "\n")
                else:
                    foriginal.write(mem.nume + ";" + mem.prenume + ";" + mem.varsta + ";" + mem.CNP.strip() + "\n")
            