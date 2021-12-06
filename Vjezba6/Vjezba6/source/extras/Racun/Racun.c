#include "Racun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (1024)

int PostavljanjeRacuna(RacunPozicija racun) {

	racun->datum = NULL;
	racun->next = NULL;
	memset(racun->naziv, 0, MAX_RACUN);
	PostavljanjeArtikla(&racun->artikalHead);
	
	return EXIT_SUCCESS;
}

RacunPozicija IzradiRacun(char* racunFile) {

	FILE* dat = NULL;
	RacunPozicija racun = NULL;
	int brKaraktera = EXIT_SUCCESS;
	char Linija[MAX] = { 0 };

	dat = fopen(racunFile, "r");

	if (!dat) {
		perror(" Racun nije pronadjen!");

		return NULL;
	}

	racun = (RacunPozicija)malloc(sizeof(Racun));
	
	if (!racun) {
		perror(" Nije moguce alocirati memoriju za racun!");
		fclose(dat);
		return NULL;
	}

	PostavljanjeRacuna(racun);

	strcpy(racun->naziv, racunFile);
	
	fgets(Linija, MAX, dat);
	racun->datum = ProcitajDatum(Linija);

	if (!racun->datum) {
		fclose(dat);
		BrisiRacun(racun);
		return NULL;
	}

	while (!feof(dat)) {

		ArtikalPozicija artikal = NULL;
		fgets(Linija, MAX, dat);

		if (strlen(Linija) == 0) {
			continue;
		}

		artikal = IzradiArtikal(Linija);
		if (!artikal) {
			fclose(dat);
			BrisiRacun(racun);
			return NULL;
		}

		SortiraniUnosArtikla(&racun->artikalHead, artikal);
	}
	
	fclose(dat);

	return racun;
} 

int UnesiRacunNakon(RacunPozicija trenutni, RacunPozicija racun) {

	racun->next = trenutni->next;
	trenutni->next = racun;

	return EXIT_SUCCESS;
}

int UnesiSortiraniRacun(RacunPozicija head, RacunPozicija racun) {

	RacunPozicija trenutni = head;

	while (trenutni->next != NULL && UsporediDatum(trenutni->next->datum, racun->datum) < 0) {
		trenutni = trenutni->next;
	}

	UnesiRacunNakon(trenutni, racun);

	return EXIT_SUCCESS;
}

int UcitajRacunIzDatoteke(RacunPozicija head, char* imeDat) {

	FILE* dat = NULL;
	char LINIJA[MAX] = { 0 };

	dat = fopen(imeDat, "r");

	if (!dat) {
		perror(" Racun nije pronadjen!\n");

		return BEZ_RACUNA;
	}

	while (!feof(dat)) {
		RacunPozicija racun = NULL;
		fscanf(dat, "%s", LINIJA);

		if (strlen(LINIJA) == 0)
			continue;

		racun = IzradiRacun(LINIJA);
		if (!racun) {
			fclose(dat);
			BrisiSveRacune(head);
			return GRESKA_U_IZRADI_RACUNA;
		}

		UnesiSortiraniRacun(head, racun);
	}

	fclose(dat);

	return EXIT_SUCCESS;
}

int IspisRacuna(RacunPozicija racun) {

	ArtikalPozicija artikal = NULL;

	printf("\t-------------------------------------------\n");
	printf("\tDatum => ");
	IspisDatuma(racun->datum);
	printf("\n");
	printf("\t-------------------------------------------\n");
	printf("\tArtikl===============Kol===Cijena====Iznos \n");

	for (artikal = racun->artikalHead.next; artikal != NULL; artikal = artikal ->next) {
		printf("\t");
		IspisArtikla(artikal);
		printf("\n");
	}
	printf("\t-------------------------------------------\n");
	printf("\n\n");

	return EXIT_SUCCESS;
}

int IspisSvihRacuna(RacunPozicija head) {

	RacunPozicija racun = NULL;
	int brojac = 1;

	for (racun = head->next; racun != NULL; racun = racun->next) {
		printf("\tRacun broj %d:\n", brojac);
		IspisRacuna(racun);
		brojac++;
	}

	return EXIT_SUCCESS;
}

int BrisiRacun(RacunPozicija racun) {
	if (!racun) {
		return EXIT_SUCCESS;
	}

	if (racun->datum) {
		free(racun->datum);
	}

	BrisiSveArtikle(&racun->artikalHead);
	free(racun);

	return EXIT_SUCCESS;
}

int BrisiRacunNakon(RacunPozicija headRacun) {

	RacunPozicija trenutni = headRacun->next;

	if (!trenutni) {
		return EXIT_SUCCESS;
	}

	headRacun->next = trenutni->next;
	BrisiRacun(trenutni);

	return EXIT_SUCCESS;
}

int BrisiSveRacune(RacunPozicija head) {
	
	while (head->next) {
		BrisiRacunNakon(head);
	}

	return EXIT_SUCCESS;
}