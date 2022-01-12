#define _CRT_SECURE_NO_WARNINGS

#include "Player/Player.h"
#include "Map/Map.h"
#include "Color.h"
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
	char ArrayMap[X][Y];
	char name[MAX_PLAYER_NAME] = { 0 };
	int sameName = 0;
	int PlayerDeath = 0;
	char input = '\0';
	int opened = 0;
	char ch[MAX_LINE] = { 0 };;
	int cC = 0;
	int i, j = 0;
	FILE* dat = NULL;

	printf("\n\t Please type the name of your player (10 characters max): ");
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
		
		NewPlayer->CharacterPoints = 10;

		if (opened == 0) {
			dat = fopen("Game/Map.txt", "r");
		}
		else
			dat = fopen(NewPlayer->name, "r");

		puts("\n");

		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {
				fscanf(dat, " %c", &ArrayMap[i][j]);

				if (ArrayMap[i][j] == 'S')
					printf(Green"    %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'C')
					printf(DarkBlue"    %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'T')
					printf(DarkCyan"    %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'L')
					printf(DarkYellow"    %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'X')
					printf(Green"    %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'P') {
					printf(DarkRed"    %c", ArrayMap[i][j]);
				}

				else
					printf(White"    %c", ArrayMap[i][j]);
			}
			puts("\n");
		}
		printf(White);
		fclose(dat);

		while (input != 'E') {
			
			//SystemClear();

			if (PlayerDeath != 1) {

				switch (input) {

				case 'E':

					break;

				default:

					PlayerDeath = ReadMap(&input, &opened, &NewPlayer->CharacterPoints, &cC, &NewPlayer->name);
					printf("\n\t Your stats: "DarkYellow"% d ", NewPlayer->CharacterPoints);
					printf(DarkMagenta"\n\t %d/500", WinValue - NewPlayer->CharacterPoints);
					printf(White" left to go.");
					if (PlayerDeath == 1 || NewPlayer->CharacterPoints < 0) {
						printf(DarkRed"\n\t You had your brains splattered!\n\n"White);
						dat = fopen("source\\Player\\Brain.txt", "r");
						while (!feof(dat)) {
							fgets(ch, MAX_LINE, dat);
							printf(Magenta" %s"White, ch);
						}
						fclose(dat);
						remove(NewPlayer->name);
						temp = NewPlayer;
						NewPlayer = NewPlayer->next;
						head->next = NewPlayer;
						free(temp);
						return PLAYER_DIED;
						break;
					}

					else if (NewPlayer->CharacterPoints >= WinValue) {
						printf(DarkCyan"\n\t You won the game!"White);
						input = 'E';
						break;
					}
					printf("\n\t Type E to leave or enter your moves (up - w, down - s, left - a, right - d): ");
					scanf(" %c", &input);

					break;
				}
			}

			else {
				input = 'E';
				printf(DarkRed"\n\n\t YOU DIED\n\n");
				printf("White");
				return EXIT_SUCCESS;
			}
			
		}

		printf(Cyan"\n\n\t You are entering main menu!\n"White);
	}
	dat = fopen("source\\saves\\players.txt", "w");
	for (game = head->next; game != NULL; game = game->next) {
		fprintf(dat, " %s\n", game->name);
	}
	fclose(dat);
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

	PlayerPos game = head;

	printf("\n\t This is all of your saved games: \n\n");

	if (!game) {

		printf("\t <Empty>\n");
		printf("\t===========================\n");
		return EXIT_SUCCESS;
	}
	
	for (game = head->next; game != NULL; game = game->next) {
		
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