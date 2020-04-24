#include "b_global.h"

enum columns{A, B, C, D, E, F, G, H, I, J};

columns column; 

apmatrix<char> PlaceShips()
{
	setForeColor(BWHITE);

	int x, y, z = 0;

	// First Square!

	cout << "        A  B  C  D  E  F  G  H  I  J        A  B  C  D  E  F  G  H  I  J" << flush;
	gotoxy(6, 1);

	cout << (char)201 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)187 << flush;
	
	for(x = 2; x < 21; x++)
	{
		gotoxy(5, x);

		if(x % 2 == 0)
		{
			cout << z << flush;
			z++;
		}
		else
			cout << ' ' << flush;

		cout << (char)186 << flush;
		
		setBackColor(9);
		
		cout << ' ' << flush;
		
		for(y = 0; y < 29; y++)	
		{
			cout << ' ' << flush;
		}

		setBackColor(0);

		cout << (char)186 << flush;
	}

	gotoxy(6, 21);

	cout << (char)200 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)188 << flush;

	// Second Square

	z = 0;

	gotoxy(42, 1);

	cout << (char)201 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)187 << flush;
	
	for(x = 2; x < 21; x++)
	{
		gotoxy(42, x);

		cout << (char)186 << flush;

		setBackColor(9);

		cout << ' ' << flush;
		
		for(y = 0; y < 29; y++)	
		{
			cout << ' ' << flush;
		}

		setBackColor(0);

		cout << (char)186 << flush;

		if(x % 2 == 0)
		{
			cout << z << flush;
			z++;
		}
		else
			cout << ' ' << flush;
	}

	gotoxy(42, 21);

	cout << (char)200 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)188 << flush;

	gotoxy(2, 22);

	cout << "(0) Rotate   (R) Restart   (Arrows) Move   (Enter) Place   (Q) Quit" << flush;

	apstring aircraft = "AAAAA";
	apstring battleship = "BBBB";
	apstring cruiser = "CCC";
	apstring submarine = "SSS";
	apstring destroyer = "DD";

	apvector<apstring> ships(6);

	apmatrix<char> myShips(10, 10, '\0');

	ships[0] = aircraft;
	ships[1] = battleship;
	ships[2] = cruiser;
	ships[3] = submarine;
	ships[4] = destroyer;
	ships[5] = '\0';
	
	int current = 0;
	int keyPressed = 0;
	int row = 0;
	int col = 0;
	int direction = HORIZONTAL;
	bool flag = false;


	while(current < 6)
	{
		gotoxy((col * 3) + 8, (row * 2) + 2);
		
		if(direction == HORIZONTAL)
		{
			for(x = 0; x < ships[current].length(); x++)
			{
				setBackColor(LBLUE);
				cout << ships[current][x] << flush;
				if(x != ships[current].length() - 1)
					cout << "  " << flush;
			}
		}
		else	
		{
			for(y = 0; y < ships[current].length(); y++)
			{
				setBackColor(LBLUE);
				gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
				cout << ships[current][y] << flush;		
			}
		}
		
		for(x = 0; x < 19; x++)
		{
			gotoxy(44, x + 2);
			for(y = 0; y < 29; y++)	
			{
				if((y % 3 == 0) && (x % 2 == 0))
				{
					if(myShips[x / 2][y / 3] != '\0')
						cout << myShips[x / 2][y / 3] << flush;
					else
						cout << ' ' << flush;
				}
				else
					cout << ' ' << flush;
			}
		}

		if(current == 5)
		{
			Sleep(1000);
			break;
		}

		keyPressed = newgetch();

		switch(keyPressed)
		{
		case 72 + 255: // UP
			{
				if(row == 0)
					break;
				else
				{
					gotoxy((col * 3) + 8, (row * 2) + 2);
		
					if(direction == HORIZONTAL)
					{
						for(x = 0; x < ships[current].length(); x++)
						{
							setBackColor(LBLUE);
							cout << ' ' << flush;
							if(x != ships[current].length() - 1)
								cout << "  " << flush;
						}
					}
					else	
					{
						for(y = 0; y < ships[current].length(); y++)
						{
							setBackColor(LBLUE);
							gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
							cout << ' ' << flush;		
						}
					}
					row--;
				}
			}
			break;
		case 80 + 255: // DOWN
			{
				if(direction == HORIZONTAL && row == 9)
					break;
				else if(direction == VERTICAL && row == 10 - ships[current].length())
					break;
				else
				{
					gotoxy((col * 3) + 8, (row * 2) + 2);
		
					if(direction == HORIZONTAL)
					{
						for(x = 0; x < ships[current].length(); x++)
						{
							setBackColor(LBLUE);
							cout << ' ' << flush;
							if(x != ships[current].length() - 1)
								cout << "  " << flush;
						}
					}
					else	
					{
						for(y = 0; y < ships[current].length(); y++)
						{
							setBackColor(LBLUE);
							gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
							cout << ' ' << flush;		
						}
					}
					row++;
				}
			}
			break;
		case 75 + 255: // LEFT
			{	
				if(col == 0)
					break;
				else
				{
					gotoxy((col * 3) + 8, (row * 2) + 2);
		
					if(direction == HORIZONTAL)
					{
						for(x = 0; x < ships[current].length(); x++)
						{
							setBackColor(LBLUE);
							cout << ' ' << flush;
							if(x != ships[current].length() - 1)
								cout << "  " << flush;
						}
					}
					else	
					{
						for(y = 0; y < ships[current].length(); y++)
						{
							setBackColor(LBLUE);
							gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
							cout << ' ' << flush;		
						}
					}
					col--;
				}
			}
			break;
		case 77 + 255: // RIGHT
			{
				if(direction == HORIZONTAL && col == 10 - ships[current].length())
					break;
				else if(direction == VERTICAL && col == 9)
					break;
				else
				{
					gotoxy((col * 3) + 8, (row * 2) + 2);
		
					if(direction == HORIZONTAL)
					{
						for(x = 0; x < ships[current].length(); x++)
						{
							setBackColor(LBLUE);
							cout << ' ' << flush;
							if(x != ships[current].length() - 1)
								cout << "  " << flush;
						}
					}
					else	
					{
						for(y = 0; y < ships[current].length(); y++)
						{
							setBackColor(LBLUE);
							gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
							cout << ' ' << flush;		
						}
					}
					col++;
				}
			}
			break;
		case 13:
			{
				if(direction == HORIZONTAL)
				{
					gotoxy((col * 3) + 8, (row * 2) + 2);

					for(x = 0; x < ships[current].length(); x++)
					{
						setBackColor(LBLUE);
						cout << ' ' << flush;
						if(x != ships[current].length() - 1)
							cout << "  " << flush;
					}
				}
				else	
				{
					for(y = 0; y < ships[current].length(); y++)
					{
						setBackColor(LBLUE);
						gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
						cout << ' ' << flush;		
					}
				}
				
				for(x = 0; x < ships[current].length(); x++)
				{
					if(direction == HORIZONTAL)
					{
						if(myShips[row][col + x] != '\0')
						{
							flag = true;
							break;
						}
					}
					else
					{
						if(myShips[row + x][col] != '\0')
						{
							flag = true;
							break;
						}
					}
				}
				
				if(flag == false)
				{
					for(x = 0; x < ships[current].length(); x++)
					{
						if(direction == HORIZONTAL)
						{
							myShips[row][col + x] = ships[current][x];
						}
						else
						{
							myShips[row + x][col] = ships[current][x];
						}
					}
					current++;
				}

				flag = false;
			}
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'R':
		case 'r':
			{
				current = 0;
				for(x = 0; x < 10; x ++)
					for(y = 0; y < 10; y++)
						myShips[x][y] = '\0';
					break;
			}
		case '0':
			{
				if(direction == HORIZONTAL)
				{
					gotoxy((col * 3) + 8, (row * 2) + 2);

					for(x = 0; x < ships[current].length(); x++)
					{
						setBackColor(LBLUE);
						cout << ' ' << flush;
						if(x != ships[current].length() - 1)
							cout << "  " << flush;
					}
				}
				else	
				{
					for(y = 0; y < ships[current].length(); y++)
					{
						setBackColor(LBLUE);
						gotoxy((col * 3) + 8, ((row + y) * 2) + 2);
						cout << ' ' << flush;		
					}
				}
				
				if(direction == HORIZONTAL && row <= 10 - ships[current].length())
					direction = VERTICAL;
				else if(col <= 10 - ships[current].length())
					direction = HORIZONTAL;
			}
			break;
		default:
			break;
		}
	}
	gotoxy(0, 22);	
	return myShips;
}

void Draw()
{
	setForeColor(15);

	int y, x, z = 0;
	
	clrscr();
	
	// First Square!

	cout << "        A  B  C  D  E  F  G  H  I  J        A  B  C  D  E  F  G  H  I  J" << flush;
	gotoxy(6, 1);

	cout << (char)201 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)187 << flush;
	
	for(x = 2; x < 21; x++)
	{
		gotoxy(5, x);

		if(x % 2 == 0)
		{
			cout << z << flush;
			z++;
		}
		else
			cout << ' ' << flush;

		cout << (char)186 << flush;
		
		setBackColor(9);
		
		cout << ' ' << flush;
		
		for(y = 0; y < 29; y++)	
		{
			if((y % 3 == 0) && (x % 2 == 0))
			{
				if(g.myGuesses[(x / 2) - 1][y / 3] == 0)
				{
					cout << ' ' << flush;
				}
				else if(g.myGuesses[(x / 2) - 1][y / 3] == 1)
				{	
					setForeColor(BWHITE);
					cout << (char)15 << flush;
				}
				else if(g.myGuesses[(x / 2) - 1][y / 3] == 2)
				{
					setForeColor(RED);
					cout << (char)15 << flush;
					setForeColor(BWHITE);
				}
			}
			else
				cout << ' ' << flush;
		}

		setBackColor(BLACK);

		cout << (char)186 << flush;
	}

	gotoxy(6, 21);

	cout << (char)200 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)188 << flush;

	// Second Square

	z = 0;

	gotoxy(42, 1);

	cout << (char)201 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)187 << flush;
	
	for(x = 2; x < 21; x++)
	{
		gotoxy(42, x);

		cout << (char)186 << flush;

		setBackColor(9);

		cout << ' ' << flush;
		
		for(y = 0; y < 29; y++)	
		{
			if((y % 3 == 0) && (x % 2 == 0))
			{
				if(g.otherGuesses[(x / 2) - 1][y / 3] == 0)
				{
					if( g.myShips[(x / 2) - 1][y / 3] != '\0')
						cout << g.myShips[(x / 2) - 1][y / 3] << flush;
					else
					{
						cout << ' ' << flush;
					}
				}
				else if(g.otherGuesses[(x / 2) - 1][y / 3] == 1)
				{	
					cout << (char)15 << flush;
				}
				else if(g.otherGuesses[(x / 2) - 1][y / 3] == 2)
				{
					setForeColor(4);
					cout << (char)15 << flush;
					setForeColor(15);
				}
			}
			else
				cout << ' ' << flush;
		}

		setBackColor(0);

		cout << (char)186 << flush;

		if(x % 2 == 0)
		{
			cout << z << flush;
			z++;
		}
		else
			cout << ' ' << flush;
	}

	gotoxy(42, 21);

	cout << (char)200 << flush;

	for(x = 0; x < 30; x++)
		cout << (char)205 << flush;

	cout << (char)188 << flush;
	
	
}

void Move(char &row, char &col)
{
	gotoxy(5, 23);

	cout << "Your Turn:  Row -      Col -" << flush;
	
	char temp;

	while(1)
	{
		gotoxy(23, 23);
		cout << ' ' << flush;
		gotoxy(23, 23);

		temp = getche();
		
		if(temp >= '0' && temp <= '9')
			break;
		
	}

	row = temp;

	while(1)
	{
		gotoxy(34, 23);
		cout << ' ' << flush;
		gotoxy(34, 23);

		temp = getche();

		if((temp >= 'A' && temp <= 'J') || (temp >= 'a' && temp <= 'j'))
			break;

	}

	col = temp;
}

int charToInt(char letter)
{
	if (letter == 'A' || letter == 'a')
		return 0;
	if (letter == 'B' || letter == 'b')
		return 1;
	if (letter == 'C' || letter == 'c')
		return 2;
	if (letter == 'D' || letter == 'd')
		return 3;
	if (letter == 'E' || letter == 'e')
		return 4;
	if (letter == 'F' || letter == 'f')
		return 5;
	if (letter == 'G' || letter == 'g')
		return 6;
	if (letter == 'H' || letter == 'h')
		return 7;
	if (letter == 'I' || letter == 'i')
		return 8;
	if (letter == 'J' || letter == 'j')
		return 9;

	return -1;
}

bool isTaken(apmatrix<int> mat, char row, char col)
{

	if (mat[atoi(&row)][charToInt(col)] == 1 || mat[atoi(&row)][charToInt(col)] == 2)
		return true;
	else
		return false;
}

void processMyMove(char row, char col)
{
	if (g.otherShips[atoi(&row)][charToInt(col)] != '\0')
	{
		g.myGuesses[atoi(&row)][charToInt(col)] = 2;

		if (g.otherShips[atoi(&row)][charToInt(col)] == 'B')
			g.otherShipsLeft[0]--;
		else if (g.otherShips[atoi(&row)][charToInt(col)] == 'A')
			g.otherShipsLeft[1]--;
		else if (g.otherShips[atoi(&row)][charToInt(col)] == 'S')
			g.otherShipsLeft[2]--;
		else if (g.otherShips[atoi(&row)][charToInt(col)] == 'C')
			g.otherShipsLeft[3]--;
		else if (g.otherShips[atoi(&row)][charToInt(col)] == 'D')
			g.otherShipsLeft[4]--;
	}
	else
		g.myGuesses[atoi(&row)][charToInt(col)] = 1;
}

void processMove(char row, char col)
{
	if (g.myShips[atoi(&row)][charToInt(col)] != '\0')
	{
		g.otherGuesses[atoi(&row)][charToInt(col)] = 2;

		if (g.myShips[atoi(&row)][charToInt(col)] == 'B')
			g.myShipsLeft[0]--;
		else if (g.myShips[atoi(&row)][charToInt(col)] == 'A')
			g.myShipsLeft[1]--;
		else if (g.myShips[atoi(&row)][charToInt(col)] == 'S')
			g.myShipsLeft[2]--;
		else if (g.myShips[atoi(&row)][charToInt(col)] == 'C')
			g.myShipsLeft[3]--;
		else if (g.myShips[atoi(&row)][charToInt(col)] == 'D')
			g.myShipsLeft[4]--;
	}
	else
		g.otherGuesses[atoi(&row)][charToInt(col)] = 1;
}
		
