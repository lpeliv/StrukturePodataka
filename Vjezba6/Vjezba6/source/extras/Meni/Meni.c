#include "extras/Filter/Filter.h"
#include "extras/Meni/Meni.h"
#include "extras/Racun/Racun.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_IME_DATOTEKE (1024)

int Meni(RacunPozicija head) {
	
	int ispitivac = EXIT_FAILURE;
	char imeDat[MAX_IME_DATOTEKE] = { 0 };
	char unos = "";
	FilterPozicija filter = NULL;

	while (ispitivac != EXIT_SUCCESS) {

		printf("\n || Unesite ime datoteke (oblika 'naziv'.txt): ");
		scanf(" %s", imeDat);

		ispitivac = UcitajRacunIzDatoteke(head, imeDat);
	}

	if (ispitivac < EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	printf(" Datoteka %s je uspjesno ucitana: \n\n", imeDat);
	IspisSvihRacuna(head);
	
	while (unos != 'H') {
		printf("\n\n || Ovo je vas izbornik:");
		printf("\n || Odaberite [A] za ponovni prikaz izbornika.\n || Filteri: \n || Odaberite [B] za izracun zarade.\n ||" 
			" Odaberite [C] za prikaz cijene najjeftinijeg artikla izmedju dva racuna.\n || Odaberite [D] za prikaz cijene najskupljeg artikla izmedju dva racuna.\n ||"
			" Odaberite [E] za ispis svih racuna.\n || Odaberite [F] za prikaz cijene najjeftinijeg artikla izmedju svih racuna.\n ||"
			" Odaberite [G] za prikaz cijene najjskupljeg artikla izmedju svih racuna.\n || Odaberite [H] za izlazak iz programa.\n");
		printf(" \n || Odaberite zeljeni unos: ");
		scanf(" %c", &unos);

		switch (unos) {
		case 'A':

			IspisSvihRacuna(head);
			
			break;

		case 'B':

			filter = IzradiFilter();
			if (filter != NULL) {
			
				IzracunajZaradu(filter, head);
				free(filter);
				filter = NULL;
			}
			break;

		case 'C':

			filter = IzradiFilter();
			if (filter != NULL) {

				PronadjiNajmanjeg(filter, head);
				free(filter);
				filter = NULL;
			}
			break;

		case 'D':

			filter = IzradiFilter();
			if (filter != NULL) {

				PronadjiNajveceg(filter, head);
				free(filter);
				filter = NULL;
			}
			break;

		case 'E':

			IspisSvihRacuna(head);
			break;

		case 'F':
			PronadjiNajmanjegOdSvih(head);
			break;

		case 'G':
			PronadjiNajvecegOdSvih(head); 
			break;

		default:
			printf("\n || Unijeli ste krivo slovo!");
			break;
		}
	}

	BrisiSveRacune(&head);

	return EXIT_SUCCESS;
}