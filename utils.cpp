// Utils.cpp - Utility fuctions
//
// All parts contributed by and copyrighted:
//		Adam Sampson    Grant Bouquet 
//		Kevin Griffin   Jared Shields

#include <windows.h>
#include <conio.h>
#include <stdarg.h>
#include <iostream>
#include <iomanip>
#include <string.h>

void clrscr()
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {0, 0};
	DWORD dw;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwSize;

	GetConsoleScreenBufferInfo(hConsole,&csbi);
	dwSize = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hConsole, 
							   ' ', 
							   dwSize, 
							   coord, 
							   &dw);
	FillConsoleOutputAttribute(hConsole,
							   csbi.wAttributes,
							   dwSize,
							   coord,
							   &dw);
	SetConsoleCursorPosition(hConsole, coord);
}

void gotoxy(int x, int y)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {x, y};
	SetConsoleCursorPosition(hConsole, coord);
}

void setForeColor(int c)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole,&csbi);

	wAttrib = csbi.wAttributes;

	wAttrib &= ~(FOREGROUND_BLUE | 
				 FOREGROUND_GREEN | 
				 FOREGROUND_RED | 
				 FOREGROUND_INTENSITY);

	if (c & 1)
		wAttrib |= FOREGROUND_BLUE;
	if (c & 2)
		wAttrib |= FOREGROUND_GREEN;
	if (c & 4)
		wAttrib |= FOREGROUND_RED;
	if (c & 8)
		wAttrib |= FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, wAttrib);
}

void setBackColor(int c)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole,&csbi);

	wAttrib = csbi.wAttributes;

	wAttrib &= ~(BACKGROUND_BLUE | 
				 BACKGROUND_GREEN | 
				 BACKGROUND_RED | 
				 BACKGROUND_INTENSITY);

	if (c & 1)
		wAttrib |= BACKGROUND_BLUE;
	if (c & 2)
		wAttrib |= BACKGROUND_GREEN;
	if (c & 4)
		wAttrib |= BACKGROUND_RED;
	if (c & 8)
		wAttrib |= BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, wAttrib);
}

int newgetch()
{
	int temp;

	while (1)
	{
		while (!kbhit());

		temp = getch();
		if (temp == 0 || temp == 0xE0)
		{
			return getch() + 255;
		}
		else
		{
			return temp;
		}
	}

	return 0;
}

// contributed by Jared Shields
int menu(int fore, int back, char *title, int numItems, ...)
{
	CONSOLE_CURSOR_INFO cci;
	
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	va_list arg;

	char *itemName;
	int select = 1;

	va_start(arg, numItems);

	setForeColor(fore);
	setBackColor(back);
	clrscr();
	
	while (1)
	{
		cout << "*****" << title << "*****" << endl << endl;

		for (int x = 1; x <= numItems; x++)
		{
			cout << "\t" << flush;

			if (x==select)
			{
				setForeColor(back);
				setBackColor(fore);
			}

			itemName = va_arg(arg, char *);

			cout << x << ". " << itemName << flush;

			if (x==select)
			{
				setForeColor(fore);
				setBackColor(back);
			}

			cout << endl;
		}
		
		switch(newgetch())
		{
			case 72 + 255:
				select--;
				if (select == 0)
					select=numItems;
				break;
			case 80 + 255:
				select++;
				if ( select > numItems )
					select = 1;
				break;
			case 13:
				return select;
				break;
			default:
				break;
		}
		clrscr();
		va_end(arg);
		va_start(arg, numItems);
	}
	return select;
}

// contributed by Jared Shields
int menu(char *title, int numItems, ...)
{
	CONSOLE_CURSOR_INFO cci;
	
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	va_list arg;

	char *itemName;
	int select = 1;

	va_start(arg, numItems);

	setForeColor(15);
	setBackColor(0);
	clrscr();
	
	while (1)
	{
		cout << "*****" << title << "*****" << endl << endl;

		for (int x = 1; x <= numItems; x++)
		{
			cout << "\t" << flush;

			if (x==select)
			{
				setForeColor(0);
				setBackColor(15);
			}

			itemName = va_arg(arg, char *);

			cout << x << ". " << itemName << flush;

			if (x==select)
			{
				setForeColor(15);
				setBackColor(0);
			}

			cout << endl;
		}
		
		switch(newgetch())
		{
			case 72 + 255:
				select--;
				if (select == 0)
					select=numItems;
				break;
			case 80 + 255:
				select++;
				if ( select > numItems )
					select = 1;
				break;
			case 13:
				clrscr();
				return select;
				break;
			case 2:
				if (numItems <= 1)
					select = 1;
				break;
			case 3:
				if (numItems <= 2)
					select = 2;
				break;
			case 4:
				if (numItems <= 3)
				select = 3;
				break;
			case 5:
				if (numItems <= 4)
				select = 4;
				break;
			case 6:
				if (numItems <= 5)
				select = 5;
				break;
			case 7:
				if (numItems <= 6)
				select = 6;
				break;
			case 8:
				if (numItems <= 7)
				select = 7;
				break;
			case 9:
				if (numItems <= 8)
				select = 8;
				break;
			case 10:
				if (numItems <= 9)
				select = 9;
				break;
			default:
				break;
		}
		gotoxy(0, 0);
		va_end(arg);
		va_start(arg, numItems);
	}
	clrscr();
	return select;
}

// contributed by Kevin Griffin
void centerText(char *text)
{
	int length = strlen(text);
	int startPos = ((80 - length) / 2) - 1;
	cout << setw(startPos) << ' ' << flush << text << endl;
}

int SetCursorVisiblity(bool set)
{
	CONSOLE_CURSOR_INFO cci;
	
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	cci.bVisible = set;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	return 0;
}
