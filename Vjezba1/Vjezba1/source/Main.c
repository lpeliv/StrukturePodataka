#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RIJEC 128
#define LINIJA 1024

typedef struct {

	char ime[RIJEC];
	char prezime[RIJEC];
	int bodovi;

}stud;

int citac(char* Popis);
stud* aloc(int brStud, char* Popis);
int ispis(int brStud, stud* student, int najv);
int naj(int brStud, stud* student);

int main() {

	int br = 0;
	int najv = 0;

	br = citac("source/Popis.txt");

	stud* student = aloc(br, "source/Popis.txt");
	najv = naj(br, student);
	ispis(br, student, najv);

	return 0;

}

int citac(char* Popis) {

	int brojac = 0;
	FILE* dat = NULL;
	char buffer[LINIJA] = { 0 };

	dat = fopen(Popis, "r");

	if (!dat) {																				//provjera prisutnosti datoteke

		printf("Greska! Datoteka nije pronadjena!\n");
		return -1;

	}

	while (!feof(dat)) {
		fgets(buffer, LINIJA, dat);
		brojac++;
	}

	fclose(dat);

	return brojac;
}


stud* aloc(int brStud, char* Popis) {

	int br = 0;
	FILE* dat = NULL;
	stud* student = NULL;

	student = (stud*)malloc(brStud * sizeof(stud));

	dat = fopen(Popis, "r");
	if (!dat) {																				//provjera mogucnosti alokacije memorije
		printf("Greska! Memoriju nije moguce alocirati!\n");
		free(student);
		return NULL;
	}

	while (!feof(dat)) {																	//citanje datoteke
		fscanf(dat, " %s %s %d", student[br].ime, student[br].prezime, &student[br].bodovi);
		br++;
	}

	fclose(dat);

	return student;
}

int ispis(int brStud, stud* student, int najv) {

	int br = 0;
	float rel = 0.0f;

	printf(" IME \t\t PREZIME \t\t BODOVI \tRELATIVNO \n");
	printf("________________________________________________________________\n");

	for (br = 0; br < brStud; br++) {

		rel = ((float)student[br].bodovi / najv) * 100.00f;

		printf("%s \t\t %s \t\t %d \t\t %.2f \n", student[br].ime, student[br].prezime, student[br].bodovi, rel);

	}

	return 0;

}

int naj(int brStud, stud* student) {

	int br = 0;
	int najv = 0;

	for (br = 0; br < brStud; br++) {
		if (student[br].bodovi > najv)
			najv = student[br].bodovi;
	}

	return najv;
}