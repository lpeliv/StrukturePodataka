#pragma once
#include "Errors.h"
#define MAX_PLAYER_NAME (10)
#define WinValue (500)

typedef struct _playerStruct* PlayerPos;

typedef struct _playerStruct {
	
	char name[MAX_PLAYER_NAME]; //Player name
	int CharacterPoints; //Player Level
	PlayerPos next; //Pointing to next player

}PlayerStruct;

int PlayerEntry(PlayerPos head);
PlayerPos CreatePlayer(char* Name);
int PlayerList(PlayerPos head);
int Switch(PlayerPos head);