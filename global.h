#ifndef global
#define global

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

struct GAME
{
	apmatrix<char> myShips;
	apmatrix<char> otherShips;
	apmatrix<int>  myGuesses;
	apmatrix<int>  otherGuesses;
};

GAME g;

#endif