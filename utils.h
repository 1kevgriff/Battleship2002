// Utils.h - Utility header file
//
// Read header in Utils.h for copyright information

#ifndef UTIL
#define UTIL

int menu(char *title, int numItems, ...);
int menu(int fore, int back, char *title, int numItems, ...);
int newgetch();
void setBackColor(int c);
void setForeColor(int c);
void gotoxy(int x, int y);
void clrscr();
void centerText(char *text);

#define BLACK	0
#define BLUE	1
#define GREEN	2
#define CYAN	3
#define RED		4
#define PURPLE	5
#define BROWN	6
#define WHITE	7
#define GRAY	8
#define LBLUE	9
#define LGREEN	10
#define LCYAN	11
#define LRED	12
#define LPURPLE	13
#define YELLOW	14
#define BWHITE	15

#endif UTIL