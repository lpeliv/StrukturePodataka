#include "Datum.h"
#include <stdio.h>
#include <stdlib.h>

DatumPozicija ProcitajDatum(char* dat) {

	DatumPozicija datum = NULL;
	int brojEl = 0;

	if (!dat) {
		printf(" Greska! String je null!\n");
		return NULL;
	}

	datum = (DatumPozicija)malloc(sizeof(Datum));
	if (!datum) {
		perror(" Greska! Nije moguæe alocirati memoriju!");
		return NULL;
	}

	brojEl = sscanf(dat, "%d-%d-%d", &datum->godina, &datum->mjesec, &datum->dan);

	if (brojEl != 3) {
		printf(" Greska! Datum je neispravno upisan! Trazeni format je  YYYY-MM-DD! \n");
		free(datum);
		return NULL;
	}

	return datum;

}

int PretvoriDatum(char* odrediste, DatumPozicija datum) {

	if (!odrediste) {
		printf(" Greska! Odrediste je nevaljalo!\n");
		return ODREDISTE_NULL;
	}

	if (!datum) {
		sprintf(odrediste, "-");
		return EXIT_SUCCESS;
	}

	sprintf(odrediste, "%04d-%02d-%02d", datum->godina, datum->mjesec, datum->dan);
	return EXIT_SUCCESS;

}

int IspisDatuma(DatumPozicija datum) {

	char datumString[DATUM_MAX] = { 0 };

	PretvoriDatum(datumString, datum);
	printf(datumString);

	return EXIT_SUCCESS;
}

int UsporediDatum(DatumPozicija prvi, DatumPozicija drugi) {

	int razlika = prvi->godina - drugi->godina;

	if (razlika == 0) {
		razlika = prvi->mjesec - drugi->mjesec;

		if (razlika == 0) {
			razlika = prvi->dan - drugi->dan;
		}
	}

	return razlika;
}

bool GranicaDatuma(DatumPozicija datum, DatumPozicija donja, DatumPozicija gornja) {

	return UsporediDatum(datum, donja) >= 0 && UsporediDatum(datum, gornja) <= 0;
}