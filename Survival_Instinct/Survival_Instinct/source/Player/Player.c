#define _CRT_SECURE_NO_WARNINGS

#include "Player/Player.h"
#include "Map/Map.h"
#include "Menu/Menu.h"
#include "Errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//inserting new player
int PlayerEntry(PlayerPos head) {

	PlayerPos game = NULL;
	PlayerPos NewPlayer = NULL;
	PlayerPos temp = NULL;
	char name[MAX_PLAYER_NAME] = { 0 };
	int sameName = 0;
	int PlayerDeath = 0;
	char input = '\0';
	FILE* dat = NULL;
	
	printf("\n\t Please type the name of your player: ");
	scanf(" %s", name);
	
	for (game = head->next; game != NULL; game = game->next) {
		if (strcmp(game->name, name) == 0){
			printf("\n\t Player already exists. Please type another name!\n\n");
			return EXIT_SUCCESS;
		}
	}

	NewPlayer = CreatePlayer(name);
	
	if (!NewPlayer) {

		printf("\n\t Player can't be created! Check your memmory!\n");
		free(NewPlayer);
		return EXIT_FAILURE;
	}

	else {

		dat = fopen("source\\saves\\players.txt", "r");
		while(!feof(dat))
			fscanf(dat, " %s\n", name);
		fclose(dat);
		
		InsertPlayerAfter(head, NewPlayer);
		
		while (input != 'E') {
			
			//SystemClear();

			if (PlayerDeath != 1) {

				switch (input) {

				case 'E':
					break;

				default:

					PlayerDeath = ReadMap(&input, NewPlayer->name);

					if (PlayerDeath == 1) {
						temp = NewPlayer;
						NewPlayer = NewPlayer->next;
						head->next = NewPlayer;
						free(temp);
						return PLAYER_DIED;
						break;
					}

					printf("\n\t Type E to leave or enter your moves (up - w, down - s, left - a, right - d): ");
					scanf(" %c", &input);

					break;
				}
			}

			else {
				input = 'E';
				printf("\n\n\t\033[1;31m YOU DIED\n\n");
				printf("\033[0m");
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_SUCCESS;
}

//memory allocation for new player
PlayerPos CreatePlayer(char* Name) {

	PlayerPos NewPlayer = NULL;

	NewPlayer = (PlayerPos)malloc(sizeof(PlayerStruct));

	if (!NewPlayer) {
		printf("\n\t The player couldn't have been created. Check your memmory!\n");
		return -1;
	}
	
	else {
		
		strcpy(NewPlayer->name, Name);
		NewPlayer->next = NULL;
	
		printf("\n\t You have successfully added a new player.\n\n");
		return NewPlayer;
	
	}
}

//Inserting player after head position
int InsertPlayerAfter(PlayerPos P, PlayerPos NewPlayer) {

	NewPlayer->next = P->next;
	P->next = NewPlayer;

	return EXIT_SUCCESS;
}

//printing player list
int PlayerList(PlayerPos head) {

	PlayerPos game = head->next;

	printf("\n\t This is all of your saved games: \n\n");

	if (!game) {

		printf("\t <Empty>\n");
		printf("\t===========================\n");
		return EXIT_SUCCESS;
	}
	
	for (; game != NULL; game = game->next) {
		
		printf("\t Player name: %s", game->name);
		puts("\t");
	}
	printf("\t===========================\n");

	return EXIT_SUCCESS;
}

//place selected player on top
int Switch(PlayerPos head){

	PlayerPos Prev = head;
	PlayerPos Curr = NULL;
	PlayerPos Foll = NULL;
	char name[MAX_PLAYER_NAME] = { 0 };

	printf("\n\t Please type the name of your player: ");
	scanf(" %s", &name);

	if (strcmp(Prev->next->name, name) == 0) {
		printf("\n\t Successfully loaded progress of %s!\n", &name);
		return EXIT_SUCCESS;
	}

	for (Prev = head; Prev->next != NULL; Prev = Prev->next) {


		// No need to switch if only one player is saved

		if (strcmp(Prev->next->name, name) == 0) {
			Curr = Prev->next;
			Foll = Curr->next;

			Curr->next = head->next;
			head->next = Curr;
			Prev->next = Foll;

			printf("\n\t Successfully loaded progress of %s!\n", &name);
			return EXIT_SUCCESS;
		}
	}
	
	printf("\n\t Player you are searching for is not saved. Please create new game!\n");
	
	return EXIT_SUCCESS;
			
}