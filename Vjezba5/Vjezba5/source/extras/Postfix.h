#ifndef PostfixHeader
#define PostfixHeader

typedef struct _postfix* Position;

typedef struct _postfix {

	double broj;
	Position next;

}postfix;

int Push(Position stog, double broj);	 // Postavljanje clana na pocetak stoga
Position IzradaClana(double Broj);	 // Izrada novog clana uz alokaciju memorije
int UnesiNakon(Position Broj, Position head);	 // Unosenje novog clana nakon "head" clana
int Pop(Position stog, double* odrediste);	 // Izbacivanje clanova iz stoga
int brisiNakon(Position stog);	 // Brisanje clana stoga nakon "head" clana
int Operacija(Position stog, char operacija);	 // Racunanje s operatorime '+','-','*' i '/'
int UcitajDat(Position stog, char* imeDatoteke);	 // Ucitavanje datoteke i provjera valjanosti unosa imena
int Citanje(Position stog, char* buffer);	 // Citanje znamenki i operatora
int BrisiSve(Position stog);	 // Brisanje cijelog stoga
int Meni();	 // Izbornik s naredbama za prekid i provedbu programa
int Program();	 // Osnovne provjere za unos imena datoteke
int Ispis(double prvi, double drugi, double rezultat); // Ispis rezultata funkcije

#endif !PostfixHeader