#ifndef global_h
#define global_h

#define WIN32_LEAN_AND_MEAN
#include <iostream.h>
#include <utils.h>
#include <apstring.h>
#include "cnetwork.h"
#include <apmatrix.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define VERTICAL 0
#define HORIZONTAL 1

using namespace std;

void Draw();
apmatrix<char> PlaceShips();
void Move(char &row, char &col);
int charToInt(char letter);
bool isTaken(apmatrix<int> mat, char row, char col);
void processMyMove(char row, char col);
void processMove(char row, char col);
bool checkLose();
bool checkWin();
void end(int);
void TitleScreen();
int checkSink(bool list[], bool list2[]);

struct GAME
{
	apmatrix<char> myShips;
	apmatrix<char> otherShips;
	apmatrix<int>  myGuesses;
	apmatrix<int>  otherGuesses;

	int myShipsLeft[5];
	int otherShipsLeft[5];
};

extern	GAME g;

#endif