#pragma once
#define X (15)
#define Y (30)
#define Ccount (10)

#include "Player/Player.h"

//Loading the map
int ReadMap(char* input, int* opened, int* CP, int* CC, char* Name);