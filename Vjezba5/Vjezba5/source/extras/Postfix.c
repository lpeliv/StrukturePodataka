#define _CRT_SECURE_NO_WARNINGS

#include "Postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Meni() {

	
	double broj = 0;
	int tester = 0;
	char odabir = '\0';
	
	
	printf("\n ||=======================Ovo je vas izbornik=======================||\n ||===Za nastavak programa upisite [N] === Za prekid programa upisite [P] ===|| \n");
	while (odabir != 'P') {
		printf("\n || Vas unos: ");
		scanf(" %c", &odabir);
		switch (odabir) {

		case 'N':

			Program();
			break;
		case 'P':
			break;

		default:
			printf("\n || Unijeli ste krivu vrijednost!");
			break;
		}
	}		
	/*	printf("\n Niste unijeli ispravan naziv datoteke! \n Za nastavak upisite [N]   ||   Za prekid programa upisite [P]: ");
		
		if (odabir == 'N') {
			scanf(" %s", imeDat);
			
		}
	
	}*/
	return EXIT_SUCCESS;
}

int Program() {

	postfix stog = { .next = NULL, .broj = 0 };
	char* imeDat = NULL;

	imeDat = malloc(sizeof(char) * 15);
	if (!imeDat) {
		printf("\n || Nije moguce alocirati memoriju.\n");
		return EXIT_FAILURE;
	}
	
	printf("\n || Upisite ime datoteke iz koje zelite citati prefiks: ");
	scanf(" %s", imeDat);

	if (UcitajDat(&stog, imeDat) == EXIT_FAILURE) {
		printf("\n || Datoteka ne postoji!\n");
		return EXIT_FAILURE;
	}

	else
		printf("\n || Uspjesno ste ucitali datoteku.\n");
	free(imeDat);

	return EXIT_SUCCESS;
}

int Push(Position stog, double broj) {

	Position noviClan = NULL;

	noviClan = IzradaClana(broj);
	if (!noviClan) {
		printf("\n || Clan nije moguce izraditi.\n");
		return EXIT_FAILURE;
	}

	UnesiNakon(noviClan, stog);
	return EXIT_SUCCESS;
}

Position IzradaClana(double Broj) {

	Position noviClan = NULL;

	noviClan = (Position)malloc(sizeof(postfix));

	if (!noviClan) {
		perror("\n || Doslo je do greske! Memorija se ne moze alocirati!\n");
		return EXIT_FAILURE;
	}
	noviClan->broj = Broj;
	noviClan->next = NULL;
	return noviClan;
}

int UnesiNakon(Position Broj, Position head) {

	Broj->next = head->next;
	head->next = Broj;

	return EXIT_SUCCESS;
}

int Pop(Position stog, double* odrediste) {

	Position trenutno = stog->next;

	if (!trenutno) {
		printf("\n || Upozorenje! Datoteka nije valjana!");
		return EXIT_FAILURE;
	}
	*odrediste = trenutno->broj;
	brisiNakon(stog);

	return EXIT_SUCCESS;
}

int brisiNakon(Position stog) {

	Position prosli = stog;
	Position trenutni = NULL;

	trenutni = prosli->next;
	prosli->next = prosli->next->next;
	
	if (!trenutni) {
		printf("\n || Stog je prazan, te nema potrebe nista brisati.");
		return EXIT_FAILURE;
	}

	free(trenutni);

	return EXIT_SUCCESS;
}

int Operacija(Position stog, char operacija) {

	double rezultat = 0;
	double prvi = 0;
	double drugi = 0;

	int provjeraPrvoga = 0;
	int provjeraDrugoga = 0;

	provjeraPrvoga = Pop(stog, &prvi);
	if (provjeraPrvoga != EXIT_SUCCESS) {
		printf("\n || Nemoguce unijeti operator.");
		return EXIT_FAILURE;
	}

	provjeraDrugoga = Pop(stog, &drugi);
	if (provjeraDrugoga != EXIT_SUCCESS) {
		printf("\n || Nemoguce unijeti operator.");
		return EXIT_FAILURE;
	}

	switch (operacija) {

	case '+':

		rezultat = prvi + drugi;
		Ispis(prvi, drugi, rezultat);

		break;

	case '*':

		rezultat = prvi * drugi;
		Ispis(prvi, drugi, rezultat);
		break;
	case '-':

		rezultat = drugi - prvi;
		Ispis(prvi, drugi, rezultat);
		break;
	case '/':

		if (drugi == 0) {
			printf("\n || Upozorenje! Dijeljenje s nulom nije dozvoljeno! Provjerite svoju datoteku!\n");
			return EXIT_FAILURE;
		}
		rezultat = drugi/ prvi;
		Ispis(prvi, drugi, rezultat);
		break;

	default:
		printf("\n || Upozorenje! Program jos ne podrzava upisane operatore! \n");
		return EXIT_FAILURE;

	}

	Push(stog, rezultat);
	return EXIT_SUCCESS;
}

int UcitajDat(Position stog, char* imeDatoteke) {

	FILE* dat = NULL;
	int duljina = 0;
	char* buffer;

	dat = fopen(imeDatoteke, "rb");

	if (!dat) {
		perror("\n || Upozorenje! Datoteka nije pronadjena!");
		return EXIT_FAILURE;
	}

	fseek(dat, 0, SEEK_END);
	duljina = ftell(dat);

	buffer = (char*)calloc(duljina + 1, sizeof(char));

	if (!buffer) {
		printf("\n || Upozorenje! Buffer nije ispravan!\n");
		return EXIT_FAILURE;
	}

	rewind(dat);

	fread(buffer, sizeof(char), duljina, dat);
	printf(" || Vas prefiks izgleda ovako:  %s || \n", buffer);
	fclose(dat);

	Citanje(stog, buffer);

	free(buffer);
	return EXIT_SUCCESS;
}

int Citanje(Position stog, char* buffer) {

	char* p = buffer;
	double znamenka = 0;
	int n = 0;
	char operator = '\0';

	while (strlen(p) > 0) {

		if (sscanf(p, " %lf %n", &znamenka, &n) == 1) {

			Push(stog, znamenka);
			p += n;
		}

		else if (sscanf(p, " %c %n", &operator, &n) == 1){

				Operacija(stog, operator);
				p += n;
			}	

		else {

			BrisiSve(stog);
			return EXIT_FAILURE;
		}

	}
	return EXIT_SUCCESS;
}

int BrisiSve(Position stog) {

	Position privremeni = NULL;

	while (stog->next != NULL) {
		privremeni = stog->next;
		stog->next = privremeni->next;
		free(privremeni);
	}

	return EXIT_SUCCESS;
}

int Ispis(double prvi, double drugi, double rezultat) {

	double rez = rezultat;
	double p = prvi;
	double d = drugi;
	printf("\n || Rezultat operacije izmedju %lf i %lf je: %lf\n", d, p, rez);

	return EXIT_SUCCESS;
}