#define _CRT_SECURE_NO_WARNINGS

#include "Map.h"
#include "Player/Player.h"
#include "Menu/Menu.h"
#include <stdio.h>
#include <stdlib.h>

int ReadMap(char* input, char* name) {

	char ArrayMap[X][Y];
	FILE* fp = NULL;
	FILE* fpN = NULL;
	int i = 0;
	int j = 0;
	int PlayerX = 0;
	int PlayerY = 0;
	int movement = 2;
	int opened = 0;

	fp = fopen("Game/Map.txt", "r");
	opened = 1;

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			fscanf(fp, " %c", &ArrayMap[i][j]);

			if (ArrayMap[i][j] == 'S')
				printf("\033[0;32m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'C')
				printf("\033[1;34m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'T')
				printf("\033[0;36m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'L')
				printf("\033[1;33m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'F')
				printf("\033[1;35m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'X')
				printf("\033[0;30m   %c", ArrayMap[i][j]);

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



	switch (*input) {

	case 'w':
		if (PlayerX != 0 && ArrayMap[PlayerX - 1][PlayerY] != 'T' && ArrayMap[PlayerX - 1][PlayerY] != 'L' && ArrayMap[PlayerX - 1][PlayerY] != 'X') {
			ArrayMap[PlayerX - 1][PlayerY] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			movement = 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'T') {
			printf("\n\t Cannot move left.");
			movement = 0;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		break;
	case 's':

		if (PlayerX != 15 && ArrayMap[PlayerX + 1][PlayerY] != 'T' && ArrayMap[PlayerX + 1][PlayerY] != 'L' && ArrayMap[PlayerX + 1][PlayerY] != 'X') {
			ArrayMap[PlayerX + 1][PlayerY] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			movement = 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'T') {
			printf("\n\t Cannot move left.");
			movement = 0;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			movement = 1;
			printf("\033[0m");
			return 1;
		}

		else
			printf("\n\t Cannot move down.");

		break;

	case 'a':
		if (PlayerY != 0 && ArrayMap[PlayerX][PlayerY - 1] != 'T' && ArrayMap[PlayerX][PlayerY - 1] != 'L' && ArrayMap[PlayerX][PlayerY - 1] != 'X') {
			ArrayMap[PlayerX][PlayerY - 1] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			movement = 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'L') {
			printf("\n\t\033[1;31m You fell in lava!");
			printf("\033[0m");
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'T') {
			printf("\n\t Cannot move left.");
			movement = 0;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'X') {
			printf("\n\t\033[1;31m You fell in trap!");
			printf("\033[0m");
			movement = 1;
			return 1;
		}
		break;
	case 'd':
		if (PlayerY != 15 && ArrayMap[PlayerX][PlayerY + 1] != 'T' && ArrayMap[PlayerX][PlayerY + 1] != 'L' && ArrayMap[PlayerX][PlayerY + 1] != 'X') {
			ArrayMap[PlayerX][PlayerY + 1] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			movement = 1;
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
		break;

	default:
		printf("\n\t You typed wrong direction!");
		break;
	}

	if (movement == 1) {
		fp = fopen("Game/Map.txt", "w");

		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {

				fprintf(fp, "%c", ArrayMap[i][j]);
			}
			fprintf(fp, "\n");
		}

		fclose(fp);

		movement = 0;
	}

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {

			if (ArrayMap[i][j] == 'S')
				printf("\033[0;32m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'C')
				printf("\033[1;34m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'T')
				printf("\033[0;36m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'L')
				printf("\033[1;33m   %c", ArrayMap[i][j]);

			else if (ArrayMap[i][j] == 'F')
				printf("\033[1;35m   %c", ArrayMap[i][j]);

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
	printf("\t Your player is here: X - %d, Y - %d\n\n", PlayerX, PlayerY);
	return EXIT_SUCCESS;
}