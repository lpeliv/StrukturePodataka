#include "Filter.h"
#include <stdio.h>
#include <stdlib.h>

int IzracunajZaradu(FilterPozicija filter, RacunPozicija head) {

    RacunPozicija racun = NULL;
    int ukupnaKolicina = 0;
    float ukupnaCijena = 0.0f;

    printf("\n|| Rezultat:\n\n");

    for (racun = head->next; racun != NULL; racun = racun->next) {
        if (GranicaDatuma(racun->datum, filter->from, filter->to)) {
            ArtikalPozicija artikal = PronadjiArtikalPoNazivu(&racun->artikalHead, filter->naziv);

            if (artikal) {

                printf("\tArtikl===============Kol===Cijena====Iznos\n");
                printf("\t");
                IspisArtikla(artikal);
                ukupnaKolicina += artikal->kolicina;
                ukupnaCijena += artikal->kolicina * artikal->cijena;
            }
        }

    }

    printf("\n\n || Trazili ste \"%s\"\n || Kolicina: %d\n || Total profit %.02f\n\n", filter->naziv, ukupnaKolicina, ukupnaCijena);
    printf("=====================================\n\n");

    return EXIT_SUCCESS;
}

int PronadjiNajmanjeg(FilterPozicija filter, RacunPozicija head) {

    RacunPozicija racun = NULL;
    int ukupnaKolicina = 0;
    float ukupnaCijena = 0.0f;
    float manji = 0.0f;

    for (racun = head->next; racun != NULL; racun = racun->next) {

        ArtikalPozicija prvi = PronadjiArtikalPoNazivu(&racun->artikalHead, filter->naziv);
        racun = racun->next;
        ArtikalPozicija drugi = PronadjiArtikalPoNazivu(&racun->artikalHead, filter->naziv);
        

        if (prvi && drugi) {

            manji = UsporediArtikleNajmanji(prvi, drugi);
            printf("\n|| Najniza cijena izmedju dva odabrana racuna: \n");
            printf("\tArtikl===============Kol===Cijena====Iznos\n");
            printf("\t");

            if (prvi->cijena == manji) {
                IspisArtikla(prvi);
            }
            else {
                IspisArtikla(drugi);
            }
        }

        return EXIT_SUCCESS;
    }
}

int PronadjiNajveceg(FilterPozicija filter, RacunPozicija head) {

    RacunPozicija racun = NULL;
    int ukupnaKolicina = 0;
    float ukupnaCijena = 0.0f;
    float veci = 0.0f;

    for (racun = head->next; racun != NULL; racun = racun->next) {

        ArtikalPozicija prvi = PronadjiArtikalPoNazivu(&racun->artikalHead, filter->naziv);
        racun = racun->next;
        ArtikalPozicija drugi = PronadjiArtikalPoNazivu(&racun->artikalHead, filter->naziv);


        if (prvi && drugi) {

            veci = UsporediArtikleNajveci(prvi, drugi);
            printf("\n|| Najvisa cijena izmedju dva odabrana racuna je: \n");
            printf("\tArtikl===============Kol===Cijena====Iznos\n");
            printf("\t");

            if (prvi->cijena == veci) {
                IspisArtikla(prvi);
            }
            else {
                IspisArtikla(drugi);
            }
        }

        return EXIT_SUCCESS;
    }
}

FilterPozicija IzradiFilter() {

    FilterPozicija novi = NULL;
    char datumString[DATUM_MAX] = { 0 };
    char ime[MAX_NAZIV] = { 0 };

    novi = (FilterPozicija)malloc(sizeof(Filter));
    if (!novi) {
        printf(" Greska! Nije moguce alocirati memoriju!\n");
        return NULL;
    }

    printf(" || Unesite prvi datum: ");
    scanf(" %s", datumString);
    novi->from = ProcitajDatum(datumString);
    
    printf(" || Unesite drugi datum: ");
    scanf(" %s", datumString);
    novi->to = ProcitajDatum(datumString);

    printf(" || Unesite ime zeljenog artikla: ");
    scanf(" %s", ime);
    
    strcpy(novi->naziv, ime);

    if (novi->from != NULL)
        if(novi->to != NULL)
            if(ime != 0)
                return novi;

    return NULL;
}

