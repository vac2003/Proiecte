from colorama import Fore

class Carte(object):
    def __init__(self, nume, autor, gen, isbn):
        self.nume = nume
        self.autor = autor
        self.gen = gen
        self.isbn = isbn # isbn = International Standard Book Number https://www.wingspublication.com/what-is-isbn/
        self.imprumutat = False

    def __str__(self):
        print(Fore.LIGHTCYAN_EX)

        impr = "DA" if self.imprumutat is True else "NU"
        info = ("Nume carte: " + self.nume + "\nAutor: " + self.autor + "\nGen: " + self.gen + "\nISBN: " + self.isbn + "\nImprumutata?: " + impr + "\n")
        
        return info
        




