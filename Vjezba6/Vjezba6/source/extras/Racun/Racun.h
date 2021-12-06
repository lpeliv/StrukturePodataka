#pragma once

#include "extras/Datum/Datum.h"
#include "extras/Artikal/Artikal.h"
#include "extras/Greske.h"

#define MAX_RACUN (128)

struct _racun;
typedef struct _racun* RacunPozicija;
typedef struct _racun {

	char naziv[MAX_RACUN];
	DatumPozicija datum;
	Artikal artikalHead;
	RacunPozicija next;

}Racun;

int PostavljanjeRacuna(RacunPozicija racun);
RacunPozicija IzradiRacun(char* racunFile);
int UnesiRacunNakon(RacunPozicija trenutni, RacunPozicija racun);
int UnesiSortiraniRacun(RacunPozicija head, RacunPozicija racun);
int UcitajRacunIzDatoteke(RacunPozicija head, char* imeDat);
int IspisRacuna(RacunPozicija racun);
int IspisSvihRacuna(RacunPozicija head);
int BrisiRacun(RacunPozicija racun);
int BrisiRacunNakon(RacunPozicija headRacun);
int BrisiSveRacune(RacunPozicija head);