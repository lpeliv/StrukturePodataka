#define _CRT_SECURE_NO_WARNINGS

#include "Map.h"
#include "Player/Player.h"
#include "Menu/Menu.h"
#include "Chest/Chest.h"
#include <stdio.h>
#include <stdlib.h>

int ReadMap(char* input, int* opened, int* CP, int* CC) {

	char ArrayMap[X][Y];
	FILE* fp = NULL;
	int i = 0;
	int j = 0;
	int PlayerX = 0;
	int PlayerY = 0;
	int movement = 2;
	int total = *CP;
	int ChestCounter = *CC;

	fp = fopen("Game/Map.txt", "r");
	puts("\n");

	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			fscanf(fp, " %c", &ArrayMap[i][j]);
			if (ArrayMap[i][j] == 'P') {
				PlayerX = i;
				PlayerY = j;
			}
		}
	}

	//Moving around the map
	switch (*input) {

	case '\0':
		*CP = 0;
		break;

	case 'w':
		if (PlayerX != 0 && ArrayMap[PlayerX - 1][PlayerY] != 'T' && ArrayMap[PlayerX - 1][PlayerY] != 'L'
			&& ArrayMap[PlayerX - 1][PlayerY] != 'X' && ArrayMap[PlayerX - 1][PlayerY] != 'C') {

			ArrayMap[PlayerX - 1][PlayerY] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			ChestCounter += 1;
			movement = 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'T') {
			printf("\n\t\033[1;31m Cannot move left.");
			printf("\033[0m");
			movement = 0;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'C') {
			if (ChestCounter < Ccount) {
				printf("\n\t\033[0;31m Chest is locked for \033[1;31m%d \033[0;31m moves!", (Ccount - ChestCounter));
				break;
			}
			
			printf("\n\t\033[1;32m You opened a chest!");
			printf("\033[0m");
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf("\n\t\033[1;31m Cannot move up.");
			printf("\033[0m");
		}
		break;
	case 's':

		if (PlayerX != (X-1) && ArrayMap[PlayerX + 1][PlayerY] != 'T' && ArrayMap[PlayerX + 1][PlayerY] != 'L'
			&& ArrayMap[PlayerX + 1][PlayerY] != 'X' && ArrayMap[PlayerX + 1][PlayerY] != 'C') {

			ArrayMap[PlayerX + 1][PlayerY] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			ChestCounter += 1;
			movement = 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'T') {
			printf("\n\t\033[1;31m Cannot move left.");
			printf("\033[0m");
			movement = 0;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'C') {
			if (ChestCounter < Ccount) {
				printf("\n\t\033[0;31m Chest is locked for \033[1;31m%d \033[0;31m moves!", (Ccount - ChestCounter));
				break;
			}

			printf("\n\t\033[1;32m You opened a chest!");
			printf("\033[0m");
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf("\n\t\033[1;31m Cannot move down.");
			printf("\033[0m");
		}
		break;
	case 'a':
		if (PlayerY != 0 && ArrayMap[PlayerX][PlayerY - 1] != 'T' && ArrayMap[PlayerX][PlayerY - 1] != 'L'
			&& ArrayMap[PlayerX][PlayerY - 1] != 'X' && ArrayMap[PlayerX][PlayerY - 1] != 'C') {

			ArrayMap[PlayerX][PlayerY - 1] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			ChestCounter += 1;
			movement = 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			printf("\033[0m");
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'T') {
			printf("\n\t\033[1;31m Cannot move left.");
			printf("\033[0m");
			movement = 0;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			printf("\033[0m");
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'C') {
			if (ChestCounter < Ccount) {
				printf("\n\t\033[0;31m Chest is locked for \033[1;31m%d \033[0;31m moves!", (Ccount - ChestCounter));
				break;
			}
			printf("\n\t\033[1;32m You opened a chest!");
			printf("\033[0m");
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf("\n\t\033[1;31m Cannot move left.");
			printf("\033[0m");
		}
		break;

	case 'd':
		if (PlayerY != (Y-1) && ArrayMap[PlayerX][PlayerY + 1] != 'T' && ArrayMap[PlayerX][PlayerY + 1] != 'L'
			&& ArrayMap[PlayerX][PlayerY + 1] != 'X' && ArrayMap[PlayerX][PlayerY + 1] != 'C') {

			ArrayMap[PlayerX][PlayerY + 1] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			movement = 1;
			ChestCounter += 1;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'T') {
			printf("\n\t Cannot move left.");
			movement = 0;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'C') {
			if (ChestCounter < Ccount) {
				printf("\n\t\033[0;31m Chest is locked for \033[1;31m%d \033[0;31m moves!", (Ccount - ChestCounter));
				break;
			}

			printf("\n\t\033[1;32m You opened a chest!");
			printf("\033[0m");
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf("\n\t\033[1;31m Cannot move right.");
			printf("\033[0m");
		}
		break;

		

	default:
		printf("\n\t You typed wrong direction!");
		break;
	}

	if (movement == 1) {
		fp = fopen("Game/Map.txt", "w");

		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {

				fprintf(fp, "%c", ArrayMap[i][j]);
			}
			fprintf(fp, "\n");
		}

		fclose(fp);

		movement = 0;
	}

	puts("\n");
	if (*input != '\0') {
		for (i = 0; i < X; i++) { 
			for (j = 0; j < Y; j++) {

				if (ArrayMap[i][j] == 'S')
					printf("\033[0;32m   %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'C')
					printf("\033[1;34m   %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'T')
					printf("\033[0;36m   %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'L')
					printf("\033[1;33m   %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'X')
					printf("\033[0;32m   %c", ArrayMap[i][j]);

				else if (ArrayMap[i][j] == 'P') {

					PlayerX = i;
					PlayerY = j;
					printf("\033[1;31m   %c", ArrayMap[i][j]);
				}

				else
					printf("\033[0m   %c", ArrayMap[i][j]);
			}
			puts("\n");

			printf("\033[0m");
		}
	}

	printf("\n\t Your player is here: X - %d, Y - %d\n\n", PlayerX, PlayerY);
	*CC = ChestCounter;
	return EXIT_SUCCESS;
}