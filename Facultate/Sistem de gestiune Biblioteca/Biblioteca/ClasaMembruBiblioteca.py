# https://bibmet.ro/faq/



class Membru(object):
    def __init__(self, nume, prenume, varsta, CNP):
        self.nume = nume
        self.prenume = prenume
        self.varsta = varsta
        self.CNP = CNP
        self.carti_imprumutate = []
   
    def imprumutaCarte(self, carte):
        if carte.imprumutat == False:
            carte.imprumutat = True
            self.carti_imprumutate.append(carte)
            print(f"Membrul {self.nume} {self.prenume} a imprumutat cartea numita {carte.nume}!")
        else:
            print(f"Cartea '{carte.nume}' este indisponibila!")

    def returCarte(self, carte):
        if carte in self.carti_imprumutate: # Adica daca cartea se afla IN lista de carti imprumutate de catre membru atunci:
            carte.imprumutat = False
            self.carti_imprumutate.remove(carte)
            print(f'Cartea {carte.nume} imprumutata de catre {self.nume} {self.prenume} a fost returnata cu succes!')

    def __str__(self):
        lista_carti_imprumutate = [carte.nume for carte in self.carti_imprumutate if carte != None]
        
        return ("Nume membru: " + self.nume + "\nPrenume membru: " + self.prenume + "\nVarsta: " + self.varsta + "\nCNP: " + self.CNP + f"Carti Imprumutate: {''.join(lista_carti_imprumutate)}" + "\n")



