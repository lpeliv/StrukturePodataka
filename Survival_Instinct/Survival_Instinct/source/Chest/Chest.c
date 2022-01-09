#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <time.h>
#include "Chest.h"
#include "Player/Player.h"

int ChestReward(int* Total) {

	int i = 0;
	int reward = 0;
	int ammount = 0;
	int total = *Total;

	puts("\n");
	srand(time(NULL));

	for (; i < 3; i++) {

		reward = (rand() % (UpperValue - LowerValue + 1)) + LowerValue;
		
		if (reward >= 1 && reward < 4) {
			printf("\t You found an Iron Sword.\n");
			total += 2;
		}

		else if (reward >= 4 && reward < 5) {
			printf("\t\033[1;31m You found Poison.\n");
			printf("\033[0m");
			total -= 50;
		}

		else if (reward >= 5 && reward < 7) {
			printf("\t You found Iron Armour.\n");
			total += 2;
		}
		
		else if (reward >= 7 && reward < 10) {
			printf("\t You found Strenght Potion.\n");
			total += 4;
		}

		else if (reward >= 10 && reward < 15) {
			printf("\t You found Swiftness Potion.\n");
			total += 2;
		}

		else if (reward >= 15 && reward < 16) {
			printf("\t You found a Lightning Sword.\n");
			total += 20;
		}

		else if (reward >= 16 && reward < 17) {
			printf("\t You found Legendary Armour.\n");
			total += 30;
		}

		else if (reward >= 17 && reward < 20) {
			printf("\t You found Rare Food.\n");
			ammount = (rand() % (5 - 1 + 1) + 1);
			total += ammount * 2;
		}

		else if (reward >= 20 && reward < 35) {
			printf("\t You found Food.\n");
			ammount = (rand() % (5 - 1 + 1) + 1);
			total += ammount;
		}

		else if (reward >= 35 && reward < 60) {
			printf("\t You found Food.\n");
			ammount = (rand() % (100 - 20 + 1) + 5);
			total += ammount/20;
		}

		else if (reward >= 60 && reward < 75) {
			printf("\t You found Leather Armor.\n");
			total += 2;
		}

		else if (reward >= 75 && reward < 90) {
			printf("\t You found Wooden Sword.\n");
			total += 2;
		}

		else if (reward >= 90 && reward < 99) {
			printf("\t You found Shield.\n");
			total += 15;
		}

		else if (reward >= 99 && reward < 101) {
			printf("\t\033[1;31m You found a Mimic.\n");
			printf("\033[0m");
			total -= 80;
		}
	}
	puts("\n");	
	return total;
}