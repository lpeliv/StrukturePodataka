#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15

struct _Osoba;

typedef struct _Osoba* Position;

typedef struct _Osoba{
		
	char ime[MAX];
	char prezime[MAX];
	int godina;

	Position next;

} Osoba;

int UnosPocetni(char* Ime, char* Prezime, int Godina, Position head);
Position IzradiOsobu(char* Ime, char* Prezime, int Godina);
void UnesiNakon(Position P, Position NovaOsoba);
int Ispis(Position first);
int UnosKrajnji(char* Ime, char* Prezime, int Godina, Position head);
Position NadjiZadnjeg(Position head);
int PronadjiPrezime(char* Prezime, Position first);
int BrisiNakon(char* Prezime, Position head);

int main(int argc, char** argv) {

	char unos = "";
	char Ime[MAX], Prezime[MAX];
	int Godina;

	Osoba Head = { .next = NULL, .ime = {0}, .prezime = {0}, .godina = 0 };
	Position p = &Head;

	printf("\nOvo je vas izbornik: \n");
	printf("----------------------------------------\n");

	printf("| Za unos prvog clana unesite 1\n");
	printf("| Za ispis svih clanova unesite 2\n");
	printf("| Za unos clana na kraju unesite 3\n");
	printf("| Za pronalazak nekog clana po prezimenu unesite 4\n");
	printf("| Za brisanje nekog clana unesite 5\n");
	printf("| Za prekid programa unesite 6\n");
	
	
	while (unos != '6') {
		printf("\n");
		scanf(" %c", &unos);

		switch (unos) {

		case '1':

			printf("Unesite ime: ");
			scanf(" %s", Ime);

			printf("Unesite prezime: ");
			scanf(" %s", Prezime);

			printf("Unesite godinu: ");
			scanf(" %d", &Godina);

			unos = IzradiOsobu(Ime, Prezime, Godina);
			UnosPocetni(Ime, Prezime, Godina, &Head);

			printf("\nStudent je uspjesno dodan na pocetak.\n");
			break;

		case '2':

			Ispis(&Head);
			break;

		case '3':

			printf("Unesite ime: ");
			scanf(" %s", Ime);

			printf("Unesite prezime: ");
			scanf(" %s", Prezime);

			printf("Unesite godinu: ");
			scanf(" %d", &Godina);

			unos = IzradiOsobu(Ime, Prezime, Godina);
			UnosKrajnji(Ime, Prezime, Godina, &Head);

			printf("\nStudent je uspjesno dodan na kraj.\n");
			break;

		case '4':

			printf("Unesite prezime studenta kojeg trazite: ");
			scanf(" %s", Prezime);

			PronadjiPrezime(Prezime, p);
			break;

		case '5':

			printf("Unesite prezime studenta kojeg zelite izbrisati: ");
			scanf(" %s", Prezime);

			BrisiNakon(Prezime, p);
			break;

		}
	}
	return EXIT_SUCCESS;
}


int UnosPocetni(char* Ime, char* Prezime, int Godina, Position head) {

	Position NovaOsoba = NULL;

	NovaOsoba = IzradiOsobu(Ime, Prezime, Godina);
	if (!NovaOsoba)
		return -1;
		
	UnesiNakon(head, NovaOsoba);
	
	return EXIT_SUCCESS;
}

Position IzradiOsobu(char* Ime, char* Prezime, int Godina) {

	Position NovaOsoba = NULL;

	NovaOsoba = (Position)malloc(sizeof(Osoba));

	if (!NovaOsoba) {
		perror("Greska! Memoriju nije mogu alocirati!");
		return -1;
	}

	strcpy(NovaOsoba->ime, Ime);
	strcpy(NovaOsoba->prezime, Prezime);
	NovaOsoba->godina = Godina;
	NovaOsoba->next = NULL;

	return NovaOsoba;
}

void UnesiNakon(Position P, Position NovaOsoba) {

	NovaOsoba->next = P->next;
	P->next = NovaOsoba;
	
}

int Ispis(Position first) {

	Position q = first->next;

	printf("\n Vasa lista izgleda ovako: \n");
	printf("| Ime             || Prezime             || Godina rodjenja \n");
	printf("-----------------------------------------------------------\n");
	for (q = first->next; q != NULL; q = q->next) {

		printf("| %-15s || %-19s || %d\n", q->ime, q->prezime, q->godina);
		
	}

	return EXIT_SUCCESS;

}
int UnosKrajnji(char* Ime, char* Prezime, int Godina, Position head) {

	Position NovaOsoba = NULL;
	Position last = NULL;

	NovaOsoba = IzradiOsobu(Ime, Prezime, Godina);
	if (!NovaOsoba)
		return -1;
	last = NadjiZadnjeg(head);

	UnesiNakon(last, NovaOsoba);


	return EXIT_SUCCESS;
}

Position NadjiZadnjeg(Position head) {

	Position q = head;
	while (q->next)
		q = q->next;

	return q;
}

int PronadjiPrezime(char* Prezime, Position first) {

	Position q = first;

	for (q = first->next; q!= NULL; q = q->next) {
		if (strcmp(q->prezime, Prezime) == 0) {

			printf("\n Trazite osobu: \n");
			printf("| Ime             || Prezime             || Godina rodjenja \n");
			printf("-----------------------------------------------------------\n");
			printf("| %-15s || %-19s || %d\n", q->ime, q->prezime, q->godina);

			return EXIT_SUCCESS;
		}

				
	}
	if (q == NULL) {
		printf("Osoba ne postoji.\n");
	}
}

int BrisiNakon(char* Prezime, Position head) {
	
	Position prosli = head;
	Position trenutni = NULL;

	for (prosli = head; prosli->next != NULL; prosli = prosli->next) {
		if (strcmp(prosli->next->prezime, Prezime) == 0) {

			trenutni = prosli->next;
			prosli->next = prosli->next->next;
			free(trenutni);

			printf("Izbrisali ste osobu %s. \n", Prezime);
			break;
		}

	}

	if (prosli->next == NULL) {
		printf("Osoba ne postoji.\n");
	}

	return EXIT_SUCCESS;
}