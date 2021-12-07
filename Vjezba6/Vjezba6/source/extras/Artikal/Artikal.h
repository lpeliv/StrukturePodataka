#pragma once

#include "extras/Greske.h"
#include "extras/Datum/Datum.h"

#define MAX_NAZIV (128)

struct _artikal;
typedef struct _artikal* ArtikalPozicija;
typedef struct _artikal {

	char ime[MAX_NAZIV];
	int kolicina;
	float cijena;
	ArtikalPozicija next;
	DatumPozicija datum;

}Artikal;

int PostavljanjeArtikla(ArtikalPozicija artikal);
ArtikalPozicija IzradiArtikal(char* str);
int PretvoriArtikal(char* odrediste, ArtikalPozicija artikal);
int IspisArtikla(ArtikalPozicija artikal);
ArtikalPozicija PronadjiArtikalPoNazivu(ArtikalPozicija head, char* naziv);
int BrisiNakonArtikla(ArtikalPozicija head);
int BrisiSveArtikle(ArtikalPozicija head);
int UnesiNakonArtikla(ArtikalPozicija trenutni, ArtikalPozicija artikal);
int SortiraniUnosArtikla(ArtikalPozicija head, ArtikalPozicija artikal);
float UsporediArtikleNajmanji(ArtikalPozicija prvi, ArtikalPozicija drugi);
float UsporediArtikleNajveci(ArtikalPozicija prvi, ArtikalPozicija drugi);