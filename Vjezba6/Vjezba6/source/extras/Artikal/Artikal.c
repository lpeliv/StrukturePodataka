#include "Artikal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME (1024)

int PostavljanjeArtikla(ArtikalPozicija artikal) {
	artikal->kolicina = 0;
	artikal->cijena = 0;
	memset(artikal->ime, 0, MAX_NAZIV);
	artikal->next = NULL;

	return EXIT_SUCCESS;
}

ArtikalPozicija IzradiArtikal(char* str) {
	
	ArtikalPozicija artikal = NULL;
	int brClanova = 0;

	if (!str) {

		printf(" Greška! String je null!\n");
		return NULL;
	}

	artikal = (ArtikalPozicija)malloc(sizeof(Artikal));
	
	if (!artikal) {
		perror(" Greska! Nije moguæe alocirati memoriju!");
		return NULL;

	}

	PostavljanjeArtikla(artikal);

	brClanova = sscanf(str, "%s %d %f", &artikal->ime, &artikal->kolicina, &artikal->cijena);

	if (brClanova != 3) {
		printf("Artikal je nevaljal! Trazeni format je <naziv> <kolicina> <cijena>!\n");
		free(artikal);
		return NULL;
	}
	
	return artikal;
}

int PretvoriArtikal(char* odrediste, ArtikalPozicija artikal) {

	float iznos = 0.0;

	if (!odrediste) {
		printf(" Greska! Odrediste je nevaljalo!\n");
		return ODREDISTE_NULL;
	}

	if (!artikal) {
		sprintf(odrediste, "##NEVALJAL ARTIKAL");
		return STRING_NEVALJAL;
	}
	iznos = artikal->kolicina * artikal->cijena;

	sprintf(odrediste, "%-20s  %-5d %-8.02f %.02f", artikal->ime, artikal->kolicina, artikal->cijena, iznos);
	return EXIT_SUCCESS;

}

int IspisArtikla(ArtikalPozicija artikal) {
	char artikalString[MAX_NAZIV] = { 0 };

	PretvoriArtikal(artikalString, artikal);
	printf(artikalString);

	return EXIT_SUCCESS;
}

ArtikalPozicija PronadjiArtikalPoNazivu (ArtikalPozicija head, char* naziv) {

	ArtikalPozicija trazeni = NULL;

	for (trazeni = head; trazeni != NULL; trazeni = trazeni->next){
		
		if (strcmp(trazeni->ime, naziv) == 0)
			return trazeni;
	}
	
	return NULL;
}

int BrisiNakonArtikla(ArtikalPozicija head) {

	ArtikalPozicija temp = head->next;

	if (temp) {
	
		head->next = temp->next;
		free(temp);

		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;

}

int BrisiSveArtikle(ArtikalPozicija head) {
	
	while (head->next) {
		BrisiNakonArtikla(head);
	}

	return EXIT_SUCCESS;
}

int UnesiNakonArtikla(ArtikalPozicija trenutni, ArtikalPozicija artikal) {

	artikal->next = trenutni->next;
	trenutni->next = artikal;

	return EXIT_SUCCESS;
}

int SortiraniUnosArtikla(ArtikalPozicija head, ArtikalPozicija artikal) {

	ArtikalPozicija trenutni = head;

	while (trenutni->next != NULL && strcmp(trenutni->next->ime, artikal->ime) < 0)
		trenutni = trenutni->next;
	
	UnesiNakonArtikla(trenutni, artikal);

	return EXIT_SUCCESS;
}

float UsporediArtikleNajmanji(ArtikalPozicija prvi, ArtikalPozicija drugi) {


	if (prvi->cijena > drugi->cijena)
		return drugi->cijena;
	else
		return prvi->cijena;
}

float UsporediArtikleNajveci(ArtikalPozicija prvi, ArtikalPozicija drugi) {


	if (prvi->cijena < drugi->cijena)
		return drugi->cijena;
	else
		return prvi->cijena;
}