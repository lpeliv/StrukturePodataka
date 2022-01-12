#define _CRT_SECURE_NO_WARNINGS

#include "Color.h"
#include "Enemy.h"
#include "Chest/Chest.h"
#include <time.h>
#include <stdio.h>

int EnemySpawner(int *playerLevel) {

	int spawner = 0; //Chance to spawn an enemy
	int Chance = 0; //Fight victory chance
	int NewStats = *playerLevel; //Player level
	int EnemyStats = 0; //Enemy level
	FILE* enemy = NULL;
	char ch[MAX_LINE] = { 0 };

	srand(time(NULL));

	//Enemy Spawn Chance
	spawner = (rand() % (UpperValue - LowerValue + 1)) + LowerValue; 
	
	//Termitnator
	if (spawner >= 1 && spawner <= 3) {

		EnemyStats = (NewStats/2 + NewStats/4) + 2;
		printf(DarkRed"\t You encountered Termitnator level %d.\n\n", EnemyStats);
		printf(White);

		enemy= fopen("source\\Enemy\\Termitnator.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		Chance = (rand() % ((NewStats + NewStats/4) - (EnemyStats - EnemyStats/4) + 1)) + (EnemyStats - EnemyStats / 4);

		if (Chance > NewStats) {
			NewStats -= 8;
			printf(DarkRed"\n\t You were the target of termination! -8 points\n\n"White);
		}

		else if (Chance == NewStats) {
			printf(DarkYellow"\t\n Hasta la vista, baby!\n\n"White);
		}

		else {
			printf(DarkGreen"\n\t You saved John Corner and got a reward! +10 points\n\n"White);
			NewStats += 10;
		}

		printf(DarkCyan"\n\n\t Press Enter to continue with (de)termination."White);
		getchar();
		getchar();
	}

	//Punster
	else if (spawner >= 22 && spawner <= 26) {

		EnemyStats = (NewStats / 4 + NewStats / 6) + 2;
		printf(DarkRed"\t You encountered Punster.\n\n"White);

		enemy = fopen("source\\Enemy\\Punster.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		Chance = (rand() % ((NewStats + NewStats / 4) - (EnemyStats - EnemyStats / 8) + 1)) + (EnemyStats - EnemyStats / 8);

		if (Chance > NewStats) {
			NewStats -= 6;
			printf(DarkRed"\n\t You were too serious! -6 points\n\n"White);
		}

		else if (Chance == NewStats) {
			printf(DarkYellow"\t\n You didn't get those scars!\n\n"White);
		}

		else {
			printf(DarkGreen"\n\t You made him laugh and here is your reward! +8 points\n\n"White);
			NewStats += 8;
		}

		printf(DarkCyan"\n\n\t Press Enter to escape to socie-tea."White);
		getchar();
		getchar();
	}

	//Voldesnort
	else if (spawner >= 55 && spawner <= 58) {

		EnemyStats = (NewStats / 5 + NewStats / 7) + 2;
		printf(DarkRed"\t You encountered Voldesnort.\n\n"White);

		enemy = fopen("source\\Enemy\\Voldesnort.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		Chance = (rand() % ((NewStats + NewStats / 4) - (EnemyStats - EnemyStats / 16) + 1)) + (EnemyStats - EnemyStats / 16);

		if (Chance > NewStats) {
			NewStats -= 4;
			printf(DarkRed"\n\t You are a Boy who Lived... and came to die! -4 points\n\n"White);
		}

		else if (Chance == NewStats) {
			printf(DarkYellow"\t\n Wingardium Leviosuhhhh!\n\n"White);
		}

		else {
			printf(DarkGreen"\n\t I've got your nose! +6 points\n\n"White);
			NewStats += 6;
		}

		printf(DarkCyan"\n\n\t Press Enter to leave Fogwarts."White);
		getchar();
		getchar();
	}
	
	//Doc Oktobus
	else if (spawner >= 72 && spawner <= 76) {

	EnemyStats = (NewStats / 6 + NewStats / 8) + 2;
	printf(DarkRed"\tYou encountered Doc Oktobus.\n\n"White);

	enemy = fopen("source\\Enemy\\SquidDoc.txt", "r");
	while (!feof(enemy)) {
		fgets(ch, MAX_LINE, enemy);
		printf(" %s", ch);
	}
	fclose(enemy);

	Chance = (rand() % ((NewStats + NewStats / 4) - (EnemyStats - EnemyStats / 12) + 1)) + (EnemyStats - EnemyStats / 12);

	if (Chance > NewStats) {
		NewStats -= 5;
		printf(DarkRed"\n\t Wrong Peter! -5 points\n\n"White);
	}

	else if (Chance == NewStats) {
		printf(DarkYellow"\t\n I had you bye the throat!\n\n"White);
	}

	else {
		printf(DarkGreen"\n\t Power of sun in palm of your hands! +6 points\n\n"White);
		NewStats += 8;
	}

	printf(DarkCyan"\n\n\t Press Enter to skip Ock-tober Fest."White);
	getchar();
	getchar();
	}
	
	return NewStats;
}