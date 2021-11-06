#define _CRT_SECURE_NO_WARNINGS

#include "Polinom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Meni() {
	polinom Head = { .next = NULL, .koeficijent = 0, .potencija = 0 };
	polinom prviPol = Head;
	polinom drugiPol = Head;

	Position P = &Head;
	Position Zbroj = &Head;
	Position Umnozak = &Head;

	char unos = '\0';
	char* imeDatoteke = NULL;

	imeDatoteke = malloc(sizeof(char) * 15);
	if (!imeDatoteke) {
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

			if (Datoteka(imeDatoteke, &prviPol, &drugiPol) == EXIT_FAILURE)
				break;

			Ispis(&prviPol);
			Ispis(&drugiPol);

			BrisiClan(&prviPol);
			BrisiClan(&drugiPol);
			break;

		case 'B':

			printf("\n Upisite ime datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDatoteke);

			if (Datoteka(imeDatoteke, &prviPol, &drugiPol) == EXIT_FAILURE)
				break;

			Zbrajanje(prviPol.next, drugiPol.next, Zbroj);

			Ispis(Zbroj);
			BrisiClan(Zbroj);
			BrisiClan(&prviPol);
			BrisiClan(&drugiPol);
			break;

		case 'C':

			printf("\n Upisite ime datoteke iz koje zelite ocitati podatke: ");
			scanf(" %s", imeDatoteke);

			if (Datoteka(imeDatoteke, &prviPol, &drugiPol) == EXIT_FAILURE)
				break;

			Mnozenje(prviPol.next, drugiPol.next, Umnozak);

			Ispis(Umnozak);
			BrisiClan(Umnozak);
			BrisiClan(&prviPol);
			BrisiClan(&drugiPol);
			break;

		case 'D':

			Izbornik();
			BrisiClan(&Head);
			break;
		}
	}
}

int Datoteka(char* imeDatoteke, Position PrviPol, Position DrugiPol) {

	FILE* dat = NULL;

	char buffer[LINIJA] = { 0 };

	dat = fopen(imeDatoteke, "r");

	if (!dat) {
		perror("\n Datoteku nije moguce pronaci! ");
		return EXIT_FAILURE;
	}

	fgets(buffer, LINIJA, dat);

	if (Citanje(PrviPol, buffer) == EXIT_FAILURE)
		return EXIT_FAILURE;

	fgets(buffer, LINIJA, dat);

	if (Citanje(DrugiPol, buffer) == EXIT_FAILURE)
		return EXIT_FAILURE;

	printf("\n Datoteka je uspjesno ucitana. \n");

	fclose(dat);
	return EXIT_SUCCESS;
}

int Unos(Position P, int koef, int polin) {

	polinom* clan = NULL;
	Position prosli = P;
	Position pomocni = NULL;

	P = P->next;

	while (P != NULL && P->potencija > polin) {
		prosli = P;
		P = P->next;
	}

	if (P != NULL && P->potencija == polin) {
		P->koeficijent += koef;
		if (P->koeficijent == 0) {
			Brisanje(prosli);
		}
	}
	else {
		clan = (Position)malloc(sizeof(polinom));

		if (!clan)
		{
			perror("\nNije moguce alocirati memoriju. ");
			return -1;
		}
		clan->potencija = polin;
		clan->koeficijent = koef;
		clan->next = P;

		prosli->next = clan;
	}
	return EXIT_SUCCESS;
}

int Citanje(Position head, char* buffer) {

	char* p = buffer;
	int koeficijent = 0;
	int potencija = 0;
	int n = 0;

	while (strlen(p) > 0) {

		if (sscanf(p, " %d %d %n", &koeficijent, &potencija, &n) != 2) {

			printf("\n Ucitavanje datoteke nije uspjelo.\n");
			return EXIT_FAILURE;
		}

		Unos(head, koeficijent, potencija);
		p += n;
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

	return EXIT_SUCCESS;
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

	while (head->next != NULL) {
		Clan = head->next;
		head->next = head->next->next;
		free(Clan);
	}
	return EXIT_SUCCESS;
}

int Brisanje(Position P) {

	Position privremeni = NULL;

	privremeni = P->next;
	P->next = privremeni->next;
	free(privremeni);
	
	return EXIT_SUCCESS;
}