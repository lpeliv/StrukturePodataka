#pragma once

#include "extras/Datum/Datum.h"
#include "extras/Artikal/Artikal.h"
#include "extras/Racun/Racun.h"

typedef struct _filter* FilterPozicija;
typedef struct _filter {

	DatumPozicija from;
	DatumPozicija to;
	char naziv[MAX_NAZIV];

}Filter;

int IzracunajZaradu(FilterPozicija filter, RacunPozicija head);
int PronadjiNajmanjeg(FilterPozicija filter, RacunPozicija head);
int PronadjiNajveceg(FilterPozicija filter, RacunPozicija head);
FilterPozicija IzradiFilter();