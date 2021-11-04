#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15
struct _Osoba;

typedef struct _Osoba* Position;

typedef struct _Osoba {

	char ime[MAX];
	char prezime[MAX];
	int godina;

	Position next;

} Osoba;

int Izbornik();
int UnosPocetni(char* Ime, char* Prezime, int Godina, Position head);
Position IzradiOsobu(char* Ime, char* Prezime, int Godina);
void UnesiNakon(Position P, Position NovaOsoba);
int Ispis(Position first);
int UnosKrajnji(char* Ime, char* Prezime, int Godina, Position head);
Position NadjiZadnjeg(Position head);
int PronadjiPrezime(char* Prezime, Position first);
int BrisiNakon(char* Prezime, Position head);
int UnesiIza(char* Ime, char* Prezime, int Godina, char* PrezimeI, Position first);
int UnesiIspred(char* Ime, char* Prezime, int Godina, char* PrezimeI, Position first);
Position NadjiMjesto(int n, Position first);
int UpisiDat(char* Upis, Position first);
int Sortiraj(Position head);

int main(int argc, char** argv) {

	char izbor = '\0';
	char unos = '\0';
	char Ime[MAX] = {0};
	char Prezime[MAX] = {0};
	int Godina = 0;
	char PrezimeI[MAX] = {0};
	char zadnji = '\0';
	int upisan = 0;

	Osoba Head = { .next = NULL, .ime = {0}, .prezime = {0}, .godina = 0 };
	Position p = &Head;

	char* Upis = NULL;
	Upis = malloc(sizeof(char) * 15);
	
	if (!Upis) {
		perror("Greska! Memoriju nije mogu alocirati!");
		return -1;
	}

	Izbornik();

	while (izbor != 'I') {
		printf("\nOdaberite zeljeni unos: ");
		scanf(" %c", &izbor);

		switch (izbor) {
		case 'A':

			Izbornik();
			break;

		case 'B':

			printf("Unesite ime: ");
			scanf(" %s", Ime);

			printf("Unesite prezime: ");
			scanf(" %s", Prezime);

			printf("Unesite godinu: ");
			scanf(" %d", &Godina);

			unos = IzradiOsobu(Ime, Prezime, Godina);
			UnosPocetni(Ime, Prezime, Godina, &Head);

			printf("\nStudent/ica je uspjesno dodan na pocetak.\n");
			break;

		case 'C':

			Ispis(&Head);
			break;

		case 'D':

			printf("Unesite ime: ");
			scanf(" %s", Ime);

			printf("Unesite prezime: ");
			scanf(" %s", Prezime);

			printf("Unesite godinu: ");
			scanf(" %d", &Godina);

			unos = IzradiOsobu(Ime, Prezime, Godina);
			UnosKrajnji(Ime, Prezime, Godina, &Head);

			printf("\nStudent/ica je uspjesno dodan na kraj.\n");
			break;

		case 'E':

			printf("Unesite prezime studenta/ice kojeg trazite: ");
			scanf(" %s", Prezime);

			PronadjiPrezime(Prezime, p);
			break;

		case 'F':

			printf("Unesite prezime studenta/ice kojeg zelite izbrisati: ");
			scanf(" %s", Prezime);

			BrisiNakon(Prezime, p);
			break;

		case 'G':

			printf("Unesite prezime studenta/ice nakon kojeg zelite dodati clan: ");
			scanf(" %s", PrezimeI);

			while (p->next != NULL) {
				if (strcmp(p->next->prezime, PrezimeI) == 0) {
					printf("Unesite ime: ");
					scanf(" %s", Ime);

					printf("Unesite prezime: ");
					scanf(" %s", Prezime);

					printf("Unesite godinu: ");
					scanf(" %d", &Godina);

					UnesiIza(Ime, Prezime, Godina, PrezimeI, &Head);
					printf("Novi clan je dodan nakon studenta/ice %s.\n", PrezimeI);
					upisan = 1;
					break;
				}
				p = p->next;
			}

			if (!upisan)
				printf("Clan nije pronadjen.\n");
			p = &Head;
			upisan = 0;
			break;

		case 'H':

			printf("Unesite prezime studenta/ice prije kojeg zelite dodati clan: ");
			scanf(" %s", PrezimeI);

			while(p->next != NULL) {
				if (strcmp(p->next->prezime, PrezimeI) == 0) {

					printf("Unesite ime: ");
					scanf(" %s", Ime);

					printf("Unesite prezime: ");
					scanf(" %s", Prezime);

					printf("Unesite godinu: ");
					scanf(" %d", &Godina);

					UnesiIspred(Ime, Prezime, Godina, PrezimeI, &Head);
					printf("Novi clan je dodan prije studenta/ice %s.\n", PrezimeI);
					upisan = 1;
					break;
				}
				p = p->next;
			}

			if (!upisan)
				printf("Clan nije pronadjen.\n");
			p = &Head;
			upisan = 0;
			break;

		case 'J':

			printf("Upisite proizvoljno ime datoteke u koju zelite pohraniti svoju listu: ");
			scanf(" %s", Upis);
			UpisiDat(Upis, &Head);
			break;

		case 'K':

			printf("Upisite ime datoteke koju zelite ucitati u svoju listu: ");
			scanf(" %s", Upis);
			UcitajDat(Upis, &Head);
			break;

		case 'L':

			Sortiraj(&Head);
			break;
		}

		
	}

	int BrisiListu(p);

	return EXIT_SUCCESS;
}

int Izbornik() {

	printf("\nOvo je vas izbornik: \n");
	printf("----------------------------------------------------------\n");

	printf("| Za ponovni prikaz izbornika unesite -----------------|A|\n");
	printf("| Za unos prvog clana unesite--------------------------|B|\n");
	printf("| Za ispis svih clanova unesite -----------------------|C|\n");
	printf("| Za unos clana na kraju unesite ----------------------|D|\n");
	printf("| Za pronalazak nekog clana po prezimenu unesite ------|E|\n");
	printf("| Za brisanje nekog clana unesite ---------------------|F|\n");
	printf("| Za unos clana nakon nekog clana unesite -------------|G|\n");
	printf("| Za unos clana prije nekog clana unesite -------------|H|\n");
	printf("| Za prekid programa unesite --------------------------|I|\n");
	printf("| Za ispis liste u datoteku unesite -------------------|J|\n");
	printf("| Za upis datoteke u listu unesite --------------------|K|\n");
	printf("| Za sortiranje liste unesite -------------------------|L|\n");

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
	int tester = 0;

	for (q = first->next; q != NULL; q = q->next) {
		if (strcmp(q->prezime, Prezime) == 0) {

			printf("\n Trazite osobu: \n");
			printf("| Ime             || Prezime             || Godina rodjenja \n");
			printf("-----------------------------------------------------------\n");
			printf("| %-15s || %-19s || %d\n", q->ime, q->prezime, q->godina);
			tester = 1;
		}
	}

	if (!tester) {
		printf("Osoba ne postoji.\n");
		return EXIT_FAILURE;
	}
}

int BrisiNakon(char* Prezime, Position head) {

	Position prosli = head;
	Position trenutni = NULL;
	int tester = 0;

	for (prosli = head; prosli->next != NULL; prosli = prosli->next) {
		if (strcmp(prosli->next->prezime, Prezime) == 0) {

			trenutni = prosli->next;
			prosli->next = prosli->next->next;
			free(trenutni);

			printf("Izbrisali ste osobu %s. \n", Prezime);
			tester = 1;
			break;
		}
	}

	if (!tester) {
		printf("Osoba ne postoji.\n");
	}

	return EXIT_SUCCESS;
}

int UnesiIza(char* Ime, char* Prezime, int Godina, char* PrezimeI, Position first) {

	Position NovaOsoba = NULL;
	first = first->next;

	while (first != NULL && strcmp(first->prezime, PrezimeI) != NULL)
		first = first->next;

	if (first != NULL) {

		NovaOsoba = IzradiOsobu(Ime, Prezime, Godina);
		if (!NovaOsoba)
			return -1;

		UnesiNakon(first, NovaOsoba);

		return EXIT_SUCCESS;
	}

	else {
		printf("\nGreska! Clan kojeg trazite ne postoji!");
		return EXIT_FAILURE;
	}

}

int UnesiIspred(char* Ime, char* Prezime, int Godina, char* PrezimeI, Position first) {

	Position NovaOsoba = NULL;

	while (first->next != NULL && strcmp(first->next->prezime, PrezimeI) != NULL)
		first = first->next;

	if (first->next != NULL) {

		NovaOsoba = IzradiOsobu(Ime, Prezime, Godina);
		if (!NovaOsoba)
			return -1;

		UnesiNakon(first, NovaOsoba);

		return EXIT_SUCCESS;
	}

	else {
		printf("\nGreska! Clan kojeg trazite ne postoji!");
		return EXIT_FAILURE;
	}

}

Position NadjiMjesto(int n, Position first) {

	while (first->next != NULL && n > first->next->prezime) {

		first = first->next;
	}

	return first;
}

int UpisiDat(char* Upis, Position first) {

	FILE* dat = NULL;
	dat = fopen(Upis, "w");

	Position clan = NULL;

	for (clan = first->next; clan != NULL; clan = clan->next) {

		fprintf(dat, " %s %s %d\n", clan->ime, clan->prezime, clan->godina);
	}
	printf("Lista je upisana u datoteku.\n");
	
	fclose(dat);

	return EXIT_SUCCESS;
}

int UcitajDat(char* Upis, Position first) {
	
	FILE* dat = NULL;
	dat = fopen(Upis, "r");
	Position clan = NULL;
	char Ime[MAX] = { 0 };
	char Prezime[MAX] = { 0 };
	int Godina = 0;

	if (!dat) {
		printf("Datoteku nije moguce pronaci.\n");
		return -1;
	}

	while(!feof(dat)){
		fscanf(dat, " %s %s %d\n", Ime, Prezime, &Godina);
		UnosKrajnji(Ime, Prezime, Godina, first);
	}

	printf("Datoteka je ucitana na pocetak liste.\n");
	fclose(dat);
	return EXIT_SUCCESS;
}

int Sortiraj(Position head) {
	
	Position first = NULL;
	Position trenutni = NULL;
	Position sljedeci = NULL;
	Position temp = NULL;
	Position empty = NULL;

	if (head->next == NULL) {
		printf("Nema clanova za usporedjivanje");
		return -1;
	}
	

	while (head->next != empty) {

		trenutni = head;
		sljedeci = head->next;

		while (sljedeci->next != empty) {

				if (strcmp(sljedeci->prezime, sljedeci->next->prezime) > 0) {

					temp = sljedeci->next;
					trenutni->next = temp;
					sljedeci->next = temp->next;
					temp->next = sljedeci;
					sljedeci = temp;
				}

				trenutni = sljedeci;
				sljedeci = sljedeci->next;
		}
		empty = sljedeci;
	}

	printf("Lista je uspjesno sortirana.\n");
	return EXIT_SUCCESS;
}

int BrisiListu(Position head) {

		Position prosli = head;
		Position trenutni = NULL;

		for (prosli = head; prosli->next != NULL; prosli = prosli->next) {
			{

				trenutni = prosli->next;
				prosli->next = prosli->next->next;
				free(trenutni);

				printf("Lista je izbrisana, a memorija ociscena. \n");
				break;
			}
		}
}