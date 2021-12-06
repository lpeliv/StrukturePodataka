#include "extras/Racun/Racun.h"
#include "extras/Filter/Filter.h"
#include "extras/Meni/Meni.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

	Racun head;
	
	PostavljanjeRacuna(&head);
	Meni(&head);
	BrisiSveRacune(&head);

	return EXIT_SUCCESS;
}