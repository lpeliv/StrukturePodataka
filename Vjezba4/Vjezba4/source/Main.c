#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define X 20

typedef struct _Polinom* Position;

typedef struct _Polinom {

	int koeficijent;
	int potencija;
	Position next;

}polinom;

int Izbornik();
int Datoteka(char* imeDatoteke, int* Polinom, int* Koeficijent, Position Head);
int Unos(Position P, int koef, int polin);
int Ispis(Position head);
int Zbrajanje(Position Prva, Position Druga, Position Zbroj);
int Mnozenje(Position Prva, Position Druga, Position umnozak);
int BrisiClan(Position head);

int main() {

	polinom Head = { .next = NULL, .koeficijent = 0, .potencija = 0 };

	Position P = &Head;
	Position Zbroj = &Head;
	Position Umnozak = &Head;

	polinom datPrva = { .next = NULL };
	polinom datDruga = { .next = NULL };

	char unos = '\0';
	char* imeDatoteke = NULL;
	char* imeDat1 = NULL;
	char* imeDat2 = NULL;
	int Koeficijent = 0;
	int Polinom = 0;
		
	imeDatoteke = malloc(sizeof(char) * X);
	if (!imeDatoteke) {
		perror(" Nije moguce alocirati memoriju.\n");
		return -1;
	}

	imeDat1 = malloc(sizeof(char) * X);
	if (!imeDat1) {
		perror(" Nije moguce alocirati memoriju.\n");
		return -1;
	}

	imeDat2 = malloc(sizeof(char) * X);
	if (!imeDat2) {
		perror(" Nije moguce alocirati memoriju.\n");
		return -1;
	}
	
	Izbornik();
	while (unos != 'E') {
		printf(" \n Odaberite zeljeni unos: ");
		scanf(" %c", &unos);
		
		switch (unos) {
		case 'A':

			printf("\n Upisite ime datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDatoteke);
			
			Datoteka(imeDatoteke, Polinom, Koeficijent, P);
			
			Ispis(P);
			
			BrisiClan(P);
			break;

		case 'B':
			

			printf("\n Upisite ime prve datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDat1);

			Datoteka(imeDat1, Polinom, Koeficijent, &datPrva);

			printf("\n Upisite ime druge datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDat2);

			Datoteka(imeDat2, Polinom, Koeficijent, &datDruga);

			Zbrajanje(datPrva.next, datDruga.next, Zbroj);
			
			Ispis(Zbroj);
			BrisiClan(Zbroj);
			BrisiClan(&datPrva);
			BrisiClan(&datDruga);
			break;

		case 'C':

			printf("\n Upisite ime prve datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDat1);
			
			Datoteka(imeDat1, Polinom, Koeficijent, &datPrva);
			
			printf("\n Upisite ime druge datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDat2);

			Datoteka(imeDat2, Polinom, Koeficijent, &datDruga);
			Mnozenje(datPrva.next, datDruga.next, Umnozak);
			
			Ispis(Umnozak);
			BrisiClan(&datPrva);
			BrisiClan(&datDruga);
			BrisiClan(Umnozak);
			break;

		case 'D':

			Izbornik();
			BrisiClan(&Head);
			break;
		}
	}

	return EXIT_SUCCESS;
}

int Datoteka(char* imeDatoteke, int* Polinom, int* Koeficijent, Position Head) {

	FILE* dat = NULL;
	int polinom = Polinom;
	int koeficijent = Koeficijent;
	int tester = 0;
	
	dat = fopen(imeDatoteke, "r");

	
	while (tester != 1) {

		if (!dat) {
			perror("\n Datoteku nije moguce pronaci!\n");
			tester = 0;
			return -1;
		}

		else {
			while (!feof(dat)) {
				fscanf(dat, " %d %d", &koeficijent, &polinom);
				Unos(Head, koeficijent, polinom);
			}

			printf("\n Datoteka je uspjesno ucitana. \n");
		tester = 1;
	
		}
	}
	tester = 0;
	
	fclose(dat);
	return Unos;
}

int Unos(Position P, int koef, int polin) {

	polinom* clan = NULL;
	Position prosli = P;

	P = P->next;

	while (P != NULL && P->potencija > polin) {
		prosli = P;
		P = P->next;
	}

	if (P != NULL && P->potencija == polin)
		P->koeficijent += koef;

	else {
		clan = (Position)malloc(sizeof(polinom));

		if (!clan)
		{
			perror("\nNije moguce alocirati memoriju.\n");
			return -1;
		}
		clan->potencija = polin;
		clan->koeficijent = koef;
		clan->next = P;
		prosli->next = clan;

	}
	return EXIT_SUCCESS;
}

int Ispis(Position head) {

	Position P = head;
	P = P->next;

	printf(" \n ||-koeficijent-|-potencija-|-zapis---------||\n");
	while (P != NULL) {

		printf(" || %-11d | %-9d | %d*x^%d\n", P->koeficijent, P->potencija, P->koeficijent, P->potencija);
		P = P->next;
	}

	return EXIT_SUCCESS;

}

int Zbrajanje(Position Prva, Position Druga, Position Zbroj) {

	Position pomocni;

	while (Prva != NULL && Druga != NULL) {
		if (Prva->potencija == Druga->potencija) {
			
			Unos(Zbroj, Prva->koeficijent + Druga->koeficijent, Prva->potencija);
			Prva = Prva->next;
			Druga = Druga->next;
		}
		else if (Prva->potencija > Druga->potencija) {

			Unos(Zbroj, Prva->koeficijent, Prva->potencija);
			Prva = Prva->next;
		}
		else {
			
			Unos(Zbroj, Druga->koeficijent, Druga->potencija);
			Druga = Druga->next;
		}
	}

	if (Prva != NULL)
		pomocni = Prva;
	else
		pomocni = Druga;

	while (pomocni != NULL) {
		
		Unos(Zbroj, pomocni->koeficijent, pomocni->potencija);
		pomocni = pomocni->next;
	}

	return EXIT_SUCCESS;
}

int Izbornik() {

	printf("\n ||----------Vas izbornik za polinome-----------||\n");
	printf(" ||=============================================||\n");
	printf(" ||-Za ispis liste polinoma unesite--------[A]--||\n ");
	printf("||-Za zbrajanje polinoma unesite----------[B]--||\n ");
	printf("||-Za mnozenje polinoma unesite-----------[C]--||\n ");
	printf("||-Za ponovni prikaz izbornika unesite----[D]--||\n ");
	printf("||-Za izlazak iz programa unesite---------[E]--||\n ");

}

int Mnozenje(Position Prva, Position Druga, Position umnozak) {

	Position pomocni = Druga;

	while (Prva != NULL) {
		
		while (Druga != NULL) {
			
			Unos(umnozak, Prva->koeficijent * Druga->koeficijent, Prva->potencija + Druga->potencija);
			Druga = Druga->next;
		}

		Druga = pomocni;
		Prva = Prva->next;
	}
	return EXIT_SUCCESS;
}

int BrisiClan(Position head) {

	Position Clan = NULL;

	while(head->next != NULL){
		Clan = head->next;
		head->next = head->next->next;
		free(Clan);
	}
}