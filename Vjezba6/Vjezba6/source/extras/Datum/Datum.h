#pragma once

#include "extras/Greske.h"
#include <stdbool.h>

#define GODINA (4)
#define DAN (2)
#define MJESEC (2)
#define POVLAKA (1)
#define NULL_CH (1)
#define DATUM_MAX (GODINA + POVLAKA + MJESEC + POVLAKA + DAN + NULL_CH)

struct _datum;
typedef struct _datum* DatumPozicija;
typedef struct _datum {
	
	int godina;
	int mjesec;
	int dan;
	
}Datum;

DatumPozicija ProcitajDatum(char* str);
int PretvoriDatum(char* odrediste, DatumPozicija datum);
int IspisDatuma(DatumPozicija datum);
int UsporediDatum(DatumPozicija prvi, DatumPozicija drugi);
bool GranicaDatuma(DatumPozicija datum, DatumPozicija donja, DatumPozicija gornja);