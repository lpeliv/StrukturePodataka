#include "Map.h"
#include "Menu/Menu.h"
#include "Chest/Chest.h"
#include "Enemy/Enemy.h"
#include "Color.h"
#include <stdio.h>
#include <stdlib.h>

int ReadMap(char* input, int* opened, int* CP, int* CC, char* Name) {

	char ArrayMap[X][Y];
	FILE* fp = NULL;
	int i = 0;
	int j = 0;
	int PlayerX = 0;
	int PlayerY = 0;
	int movement = 2;
	int total = *CP;
	int ChestCounter = *CC;
	char name[MAX_PLAYER_NAME] = { 0 };

	if (*opened == 0) {
		fp = fopen("Game/Map.txt", "r");
		*opened = 1;
		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {
				fscanf(fp, " %c", &ArrayMap[i][j]);
				if (ArrayMap[i][j] == 'P') {
					PlayerX = i;
					PlayerY = j;
				}
			}
		}
		fclose(fp);

		fp = fopen(Name, "w");

		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {

				fprintf(fp, "%c", ArrayMap[i][j]);
			}
			fprintf(fp, "\n");
		}

		fclose(fp);
	}
	else
		fp = fopen(Name, "r");

	if (!fp) {
		printf("\n\t Map doesn't exist! Check your files!");
		return EXIT_SUCCESS;
	}
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

	fclose(fp);

	//Moving around the map
	switch (*input) {

	case '\0':
		break;

	case 'w':
		if (PlayerX != 0 && ArrayMap[PlayerX - 1][PlayerY] != 'T' && ArrayMap[PlayerX - 1][PlayerY] != 'L'
			&& ArrayMap[PlayerX - 1][PlayerY] != 'X' && ArrayMap[PlayerX - 1][PlayerY] != 'C') {

			ArrayMap[PlayerX - 1][PlayerY] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			*CP = EnemySpawner(&total);
			ChestCounter += 1;
			movement = 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'L') {
			printf(DarkYellow"\n\t You fell in lava!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'T') {
			printf(DarkRed"\n\t Cannot move up."White);
			movement = 0;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'X') {
			printf(DarkRed"\n\t You fell in a trap!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX - 1][PlayerY] == 'C') {
			if (ChestCounter < Ccount) {
				printf(Red"\n\t Chest is locked for "DarkRed"%d", (Ccount - ChestCounter));
				printf(Red" moves!"White);
				break;
			}
			
			printf(DarkGreen"\n\t You opened a chest!"White);
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf(DarkRed"\n\t Cannot move up."White);
		}
		break;
	case 's':

		if (PlayerX != (X-1) && ArrayMap[PlayerX + 1][PlayerY] != 'T' && ArrayMap[PlayerX + 1][PlayerY] != 'L'
			&& ArrayMap[PlayerX + 1][PlayerY] != 'X' && ArrayMap[PlayerX + 1][PlayerY] != 'C') {

			ArrayMap[PlayerX + 1][PlayerY] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			*CP = EnemySpawner(&total);
			ChestCounter += 1;
			movement = 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'L') {
			printf(DarkYellow"\n\t You fell in lava!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'T') {
			printf(DarkRed"\n\t Cannot move down."White);
			movement = 0;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'X') {
			printf(DarkRed"\n\t You fell in a trap!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX + 1][PlayerY] == 'C') {
			if (ChestCounter < Ccount) {
				printf(Red"\n\t Chest is locked for "DarkRed"%d", (Ccount - ChestCounter));
				printf(Red" moves!"White);
				break;
			}

			printf(DarkGreen"\n\t You opened a chest!"White);
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf(DarkRed"\n\t Cannot move down."White);
		}
		break;
	case 'a':
		if (PlayerY != 0 && ArrayMap[PlayerX][PlayerY - 1] != 'T' && ArrayMap[PlayerX][PlayerY - 1] != 'L'
			&& ArrayMap[PlayerX][PlayerY - 1] != 'X' && ArrayMap[PlayerX][PlayerY - 1] != 'C') {

			ArrayMap[PlayerX][PlayerY - 1] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			*CP = EnemySpawner(&total);
			ChestCounter += 1;
			movement = 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'L') {
			printf(DarkYellow"\n\t You fell in lava!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'T') {
			printf(DarkRed"\n\t Cannot move left."White);
			movement = 0;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'X') {
			printf(DarkRed"\n\t You fell in a trap!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY - 1] == 'C') {
			if (ChestCounter < Ccount) {
				printf(Red"\n\t Chest is locked for "DarkRed"%d", (Ccount - ChestCounter));
				printf(Red" moves!"White);
				break;
			}
			printf(DarkGreen"\n\t You opened a chest!"White);
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf(DarkRed"\n\t Cannot move left."White);
		}
		break;

	case 'd':
		if (PlayerY != (Y-1) && ArrayMap[PlayerX][PlayerY + 1] != 'T' && ArrayMap[PlayerX][PlayerY + 1] != 'L'
			&& ArrayMap[PlayerX][PlayerY + 1] != 'X' && ArrayMap[PlayerX][PlayerY + 1] != 'C') {

			ArrayMap[PlayerX][PlayerY + 1] = 'P';
			ArrayMap[PlayerX][PlayerY] = 'S';
			*CP = EnemySpawner(&total);
			movement = 1;
			ChestCounter += 1;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'L') {
			printf(DarkYellow"\n\t You fell in lava!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'T') {
			printf(DarkRed"\n\t Cannot move right."White);
			movement = 0;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'X') {
			printf(DarkRed"\n\t You fell in a trap!"White);
			movement = 1;
			return 1;
		}

		else if (ArrayMap[PlayerX][PlayerY + 1] == 'C') {
			if (ChestCounter < Ccount) {
				printf(Red"\n\t Chest is locked for "DarkRed"%d", (Ccount - ChestCounter));
				printf(Red" moves!"White);
				break;
			}

			printf(DarkGreen"\n\t You opened a chest!"White);
			*CP = ChestReward(&total);
			ChestCounter = 0;
			movement = 1;
		}

		else {
			printf(DarkRed"\n\t Cannot move right."White);
		}
		break;

		

	default:
		printf(DarkRed"\n\t You typed wrong direction!"White);
		break;
	}

	if (movement == 1) {
		fp = fopen(Name, "w");

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

					PlayerX = i;
					PlayerY = j;
					printf(DarkRed"    %c", ArrayMap[i][j]);
				}
				else
					printf(White"   %c", ArrayMap[i][j]);
			}
			puts("\n");
			printf(White);
		}
	}

	printf("\n\t Your player is here: X - %d, Y - %d\n\n", PlayerX, PlayerY);
	*CC = ChestCounter;

	return EXIT_SUCCESS;
}