#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Menu/Menu.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include "Color.h"

int Menu() {

	//variables

	char entry = '\0';
	char confirmation = '\0';
	PlayerStruct head = {.name = "\0", .next = NULL, .CharacterPoints = 0};
	PlayerPos P = &head;
	FILE* dat = NULL;
	FILE* MM = NULL;
	PlayerPos NewPlayer = NULL;
	char name[MAX_PLAYER_NAME] = { 0 };
	int dead = 0;
	char mm[MAX_LINE] = { 0 };

	dat = fopen("source\\saves\\players.txt", "r");
	if (dat) {
		fseek(dat, 0, SEEK_END);
		if (ftell(dat) != 0) {
			fseek(dat, 0, SEEK_SET);

			while (!feof(dat)) {

				fscanf(dat, " %s %d\n", head.name, &head.CharacterPoints);
				NewPlayer = CreatePlayer(&head.name, &head.CharacterPoints);

				while (P->next != NULL)
					P = P->next;
				P->next = NewPlayer;
				P = &head;
			}
		}
	}

	while (confirmation != 'Y') {

		//Main Menu
		MM = fopen("source\\Menu\\MainMenu.txt", "r");
		while (!feof(MM)) {
			fgets(mm, MAX_LINE, MM);
			printf(DarkWhite" %s"White, mm);
		}
		fclose(MM);

		//User Selection
		printf("\n\t Your input: ");
		scanf(" %c", &entry);
		puts("\n");

		switch (entry) {

		case 'A':
			//Starting new game
			dead = PlayerEntry(P);
			
			break;
		
		case 'B':
			if (P->next == NULL) {

				printf(Red"\n\t There is no saved games! Please start new game.\n"White);
				break;
			}

			dead = LoadPlayer(P);

			break;

		case 'C':

			PlayerList(P);
			break;

		// Exit
		case 'E':

			printf("\n\t Are you sure you want to leave the game? Type"DarkGreen"[Y]"White" for yes or "DarkRed"[N]"White" for no: ");
			scanf(" %c", &confirmation);
			while (confirmation != 'Y' || confirmation != 'N') {
				if (confirmation == 'Y') {

					printf(DarkGreen"\n\t Thank you for playing the game. Goodbye!\n"White);
					fclose(dat);
					return EXIT_SUCCESS;
				}

				else if (confirmation == 'N') {
					SystemClear();
					break;
				}
				
				else {
					SystemClear();
					printf(Red"\t You typed the wrong letter.\n"White);
				}
			}
			break;

		default:
			SystemClear();
			printf(Red"\t You typed the wrong letter.\n"White);
			break;
		}
	}

	if(dat)
		fclose(dat);
	return EXIT_SUCCESS;
}

int SystemClear() {

	system("cls");

	return 0;
}