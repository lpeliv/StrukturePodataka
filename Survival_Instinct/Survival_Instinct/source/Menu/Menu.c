#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Menu/Menu.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include <Windows.h>

int Menu() {

	//variables

	char entry = '\0';
	char confirmation = '\0';
	PlayerStruct head = {.name = "\0", .next = NULL, .element = 0};
	PlayerPos P = &head;
	FILE* dat = NULL;
	FILE* MM = NULL;
	PlayerPos NewPlayer = NULL;
	int dead = 0;
	char mm[MAX_LINE] = { 0 };


	
	dat = fopen("source\\saves\\players.txt", "r");

	if (dat) {
		while (!feof(dat)) {

			fscanf(dat, " %s\n", head.name);
			NewPlayer = CreatePlayer(&head.name);

			NewPlayer->next = P->next;
			P->next = NewPlayer;
		}
	}

	while (confirmation != 'Y') {

		//Main Menu

		MM = fopen("source\\Menu\\MainMenu.txt", "r");
		while (!feof(MM)) {
			fgets(mm, MAX_LINE, MM);
			printf(" %s", mm);
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
			if(dead == PLAYER_DIED)
			//SystemClear();
			
			break;
		
		case 'B':
			//WIP
			printf("\n\t Successfully loaded the game!\n");
			break;

		case 'C':

			//SystemClear();
			PlayerList(P);
			break;

		case 'D':
			//WIP
			// If no players are saved, skip this function
			if (P->next == NULL) {

				printf("\n\t There is no saved games! Please start new game.\n");
				break;
			}

			Switch(P);
			break;
			
		case 'E':

			break;

		// Exit
		case 'Z':

			printf("\n\t Are you sure you want to leave the game? Type [Y] for yes or [N] for no: ");
			scanf(" %c", &confirmation);
			while (confirmation != 'Y') {
				if (confirmation == 'Y') {

					printf("\n\t Thank you for playing the game. Goodbye!\n");
					fclose(dat);
					return EXIT_SUCCESS;
				}
				else
					printf("\t You typed the wrong letter.\n");
			}
			break;

		default:
			printf("\t You typed the wrong letter.\n");
			break;
		}
	}

	if(dat)
		fclose(dat);
	return EXIT_SUCCESS;
}

int SystemClear() {

	system("clear");
	//remove later
	system("pause > null");

	return 0;
}