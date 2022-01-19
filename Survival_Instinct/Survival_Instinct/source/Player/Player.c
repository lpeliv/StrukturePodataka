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
	char ch[MAX_LINE] = { 0 };
	int cC = 0;
	int cP = 0;
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

	NewPlayer = CreatePlayer(name, &cP);
	
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
		
		NewPlayer->CharacterPoints = 50;

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

			if (PlayerDeath != 1) {

				switch (input) {

				case 'E':

					break;

				default:

					PlayerDeath = ReadMap(&input, &opened, &NewPlayer->CharacterPoints, &cC, &NewPlayer->name);
					printf("\n\t Your stats: "DarkYellow"% d ", NewPlayer->CharacterPoints);
					printf(DarkMagenta"\n\t %d/500", WinValue - NewPlayer->CharacterPoints);
					printf(White" left to go.");
					if (PlayerDeath == 1 || NewPlayer->CharacterPoints <= 0) {
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

					SystemClear();
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
		fprintf(dat, " %s %d\n", game->name, game->CharacterPoints);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

//memory allocation for new player
PlayerPos CreatePlayer(char* Name, int* CP) {

	PlayerPos NewPlayer = NULL;

	NewPlayer = (PlayerPos)malloc(sizeof(PlayerStruct));

	if (!NewPlayer) {
		printf("\n\t The player couldn't have been created. Check your memmory!\n");
		return -1;
	}
	
	else {
		
		strcpy(NewPlayer->name, Name);
		NewPlayer->CharacterPoints = *CP;
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
	char empty = ' ';

	printf(DarkGreen"\n\t This is all of your saved games: \n\n"DarkWhite);

	if (game->next == NULL) {

		printf("\t Player name: <Empty>\n");
		printf("\t==================================\n");
		return EXIT_SUCCESS;
	}
	
	for (game = head->next; game != NULL; game = game->next) {
		
		printf("\t Player name: %s %10c level %d / 500", game->name, empty, game->CharacterPoints);
		puts("\t");
	}
	printf("\t================================================\n"White);

	return EXIT_SUCCESS;
}

int LoadPlayer(PlayerPos head) {


	PlayerPos game = head;
	PlayerPos temp = NULL;
	PlayerPos prev = NULL;
	PlayerPos Player = NULL;
	char ArrayMap[X][Y];
	char name[MAX_PLAYER_NAME] = { 0 };
	int PlayerDeath = 0;
	char input = '\0';
	char ch[MAX_LINE] = { 0 };
	int opened = 1;
	int cC = 0;
	int cP = 0;
	int found = 0;
	int i, j = 0;
	FILE* dat = NULL;

	printf("\n\t Please type the name of your player (10 characters max): ");
	scanf(" %s", name);
	

	for (game = head->next; game != NULL; game = game->next) {
		if (strcmp(game->name, name) == 0) {
			printf(DarkGreen"\n\t Player found.\n\n"White);
			Player = game;
			Player->CharacterPoints = game->CharacterPoints;
			found = 1;
			break;
		}
	}

	if (found != 1) {
		printf(DarkRed"\n\t Player not found.\n\n"White);
		return EXIT_SUCCESS;
	}

	dat = fopen(Player->name, "r");

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

		if (PlayerDeath != 1) {

			switch (input) {

			case 'E':

				break;

			default:

				PlayerDeath = ReadMap(&input, &opened, &Player->CharacterPoints, &cC, &Player->name);
				printf("\n\t Your stats: "DarkYellow"% d ", Player->CharacterPoints);
				printf(DarkMagenta"\n\t %d/500", WinValue - Player->CharacterPoints);
				printf(White" left to go.");

				if (PlayerDeath == 1 || Player->CharacterPoints <= 0) {
					printf(DarkRed"\n\t You had your brains splattered!\n\n"White);
					dat = fopen("source\\Player\\Brain.txt", "r");
					while (!feof(dat)) {
						fgets(ch, MAX_LINE, dat);
						printf(Magenta" %s"White, ch);
					}
					puts("\n\n"); 
					fclose(dat);

					remove(Player->name);
					for (game = head; game->next != NULL; game = game->next) {
						if (strcmp(game->next->name, Player->name) == 0) {
							
							temp = Player;
							Player = Player->next;
							game->next = Player;
							free(temp);
							break;
						}
					}

					input = 'E';
					break;
				}

				else if (Player->CharacterPoints >= WinValue) {
					printf(DarkCyan"\n\t You won the game!"White);
					input = 'E';
					break;
				}
				printf("\n\t Type E to leave or enter your moves (up - w, down - s, left - a, right - d): ");
				scanf(" %c", &input);

				SystemClear();
				break;
				
				for (game = head; game->next != NULL; game = game->next) {
					if (strcmp(game->name, Player->name) == 0) {
						game->CharacterPoints = Player->CharacterPoints;
					}
				}
			}
		}

		else {
			input = 'E';
			printf(DarkRed"\n\n\t YOU DIED\n\n"White);
		}
	}

	
	printf(Cyan"\n\n\t You are entering main menu!\n"White);

	dat = fopen("source\\saves\\players.txt", "w");
	for (game = head->next; game != NULL; game = game->next) {
		fprintf(dat, " %s %d\n", game->name, game->CharacterPoints);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}