#ifndef PolinomHeader
#define PolinomHeader

#define LINIJA 1024

typedef struct _Polinom* Position;

typedef struct _Polinom {

	int koeficijent;
	int potencija;
	Position next;

}polinom;

int Meni();
int Izbornik();
int Datoteka(char* imeDatoteke, Position PrviPol, Position DrugiPol);
int Unos(Position P, int koef, int polin);
int Ispis(Position head);
int Zbrajanje(Position Prva, Position Druga, Position Zbroj);
int Mnozenje(Position Prva, Position Druga, Position umnozak);
int BrisiClan(Position head);
int Citanje(Position head, char* buffer);
int Brisanje(Position P);

#endif !PolinomHeader