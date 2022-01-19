#include "Color.h"
#include "Enemy.h"
#include "Chest/Chest.h"
#include <time.h>
#include <stdio.h>
#include <conio.h>

int EnemySpawner(int *playerLevel) {

	int spawner = 0; //Chance to spawn an enemy
	int Chance = 0; //Fight victory chance
	float percentage = 0.0f;
	int NewStats = *playerLevel; //Player level
	int EnemyStats = 0; //Enemy level
	FILE* enemy = NULL;
	char ch[MAX_LINE] = { 0 };

	srand(time(NULL));

	//Enemy Spawn Chance
	spawner = (rand() % (UpperValue - LowerValue + 1)) + LowerValue; 
	
	//Termitnator
	if (spawner >= 1 && spawner <= 3) {

		EnemyStats = (rand() % ((NewStats + 10) - (NewStats - 30) + 1)) + (NewStats - 30);
		printf(DarkRed"\t You encountered Termitnator level %d.\n\n"White, EnemyStats);
		printf(White);

		enemy= fopen("source\\Enemy\\Termitnator.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		percentage = (float)NewStats / EnemyStats * 100.00 / 2;
		Chance = (rand() % ((EnemyStats + NewStats / 2) - (EnemyStats - NewStats / 2) + 1)) + (EnemyStats - NewStats / 2);

		if (Chance > NewStats) {
			NewStats -= 8;
			printf(DarkRed"\n\t You were the target of termination! -8 points\n\n"White);
		}

		else if (Chance == NewStats) {
			printf(DarkYellow"\n\n\t Hasta la vista, baby!\n\n"White);
		}

		else {
			printf(DarkGreen"\n\t You saved John Corner and got a reward! +10 points\n\n"White);
			NewStats += 10;
		}
		printf("\t Chances of winning were %.2f percent.", percentage);
		printf(DarkCyan"\n\n\t Press any key to continue with (de)termination."White);
		_getch();
	}

	//Punster
	else if (spawner >= 22 && spawner <= 26) {

		EnemyStats = (rand() % ((NewStats + 25) - (NewStats - 35) + 1)) + (NewStats - 35);
		printf(DarkRed"\t You encountered Punster level %d.\n\n"White, EnemyStats);

		enemy = fopen("source\\Enemy\\Punster.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		percentage = (float)NewStats / EnemyStats * 100.00 / 2;
		Chance = (rand() % ((EnemyStats + NewStats / 2) - (EnemyStats - NewStats / 2) + 1)) + (EnemyStats - NewStats / 2);

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
		printf("\t Chances of winning were %.2f percent.", percentage);
		printf(DarkCyan"\n\n\t Press any key to escape to socie-tea."White);
		_getch();
	}

	//Voldesnort
	else if (spawner >= 55 && spawner <= 58) {

		EnemyStats = (rand() % ((NewStats + 15) - (NewStats - 35) + 1)) + (NewStats - 35);
		printf(DarkRed"\t You encountered Voldesnort level %d.\n\n"White, EnemyStats);

		enemy = fopen("source\\Enemy\\Voldesnort.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		percentage = (float)NewStats / EnemyStats * 100.00 / 2;
		Chance = (rand() % ((EnemyStats + NewStats / 2) - (EnemyStats - NewStats / 2) + 1)) + (EnemyStats - NewStats / 2);

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
		printf("\t Chances of winning were %.2f percent.", percentage);
		printf(DarkCyan"\n\n\t Press any key to leave Fogwarts."White);
		_getch();
	}
	
	//Doc Oktobus
	else if (spawner >= 72 && spawner <= 76) {

		EnemyStats = (rand() % ((NewStats + 15) - (NewStats - 35) + 1)) + (NewStats - 35);
		printf(DarkRed"\tYou encountered Doc Oktobus level %d.\n\n"White, EnemyStats);

		enemy = fopen("source\\Enemy\\SquidDoc.txt", "r");
		while (!feof(enemy)) {
			fgets(ch, MAX_LINE, enemy);
			printf(" %s", ch);
		}
		fclose(enemy);

		percentage = (float)NewStats / EnemyStats * 100.00 / 2;
		Chance = (rand() % ((EnemyStats + NewStats / 2) - (EnemyStats - NewStats / 2) + 1)) + (EnemyStats - NewStats / 2);

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

		printf("\t Chances of winning were %.2f percent.", percentage);
		printf(DarkCyan"\n\n\t Press any key to skip Ock-tober Fest."White);
		_getch();
	}
	return NewStats;
}