// Battleship
#include "b_global.h"
#include <stdlib.h>
#include <wincon.h>
#include <utils.h>

GAME g;

int main()
{
	SetCursorVisibility(NULL);
	SetConsoleTitle("B A T T L E S H I P - The Online Experience");

	TitleScreen();

	int menuChoice = 0;

	CNetwork net1(true);
	CNetwork net2(true);

	apstring p1Name;
	apstring p2Name;
	bool host;

						  // battleship, aircraft, submarine, crusier, destroyer
	bool p1ShipsSunk[5] = {false, false, false, false, false};
	bool p2ShipsSunk[5] = {false, false, false, false, false};

	g.myGuesses.resize(10, 10);
	g.myShips.resize(10, 10);
	g.otherGuesses.resize(10, 10);
	g.otherShips.resize(10, 10);

	for(int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			g.myGuesses[r][c] = 0;
			g.otherGuesses[r][c] = 0;
			g.myShips[r][c] = '\0';
			g.otherShips[r][c] = '\0';
		}
	}

	g.myShipsLeft[0] = 4;
	g.myShipsLeft[1] = 5;
	g.myShipsLeft[2] = 3;
	g.myShipsLeft[3] = 3;
	g.myShipsLeft[4] = 2;

	g.otherShipsLeft[0] = 4;
	g.otherShipsLeft[1] = 5;
	g.otherShipsLeft[2] = 3;
	g.otherShipsLeft[3] = 3;
	g.otherShipsLeft[4] = 2;

	while (true)
	{
		clrscr();
		setForeColor(BWHITE);
		centerText("B A T T L E S H I P");
		setForeColor(WHITE);
		centerText("By Kevin, Matt, and Jared");
		cout << endl;
		setForeColor(BWHITE);
		cout << "Pick Game Option:" << endl;
		cout << "1) Player vs Computer (unavailable)" << endl;
		cout << "2) Player vs Player (Host)" << endl;
		cout << "3) Player vs Player (Client)" << endl;
		cout << "4) Quit" << endl;
		cout << endl;

		menuChoice = newgetch();

		if (menuChoice == '1')
		{
			boxMessage("THIS OPTION IS NOT YET AVAILABLE", RED, BLACK);
			continue;
			break;
		}
		else if (menuChoice == '2')
		{
			// setup host
			clrscr();

			host = true;
			int port = 0;
			apstring name;

			
			cout << "You are going to be the HOST of this game." << endl;
			cout << "Your IP address is: ";
			
			char ac[80];
			gethostname(ac, sizeof(ac));

			struct hostent *phe = gethostbyname(ac);
			if (phe == 0)
				cout << "ADDRESS NOT FOUND" << endl;

			for(int i = 0; phe->h_addr_list[i] != 0; i++)
			{
				struct in_addr addr;
				memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
				cout << inet_ntoa(addr) << endl;
			}

			cout << endl;
			cout << "Please enter your name: ";
			cin >> name;

			cout << "Please enter port to listen on: ";
			cin >> port;
			cout << endl;

			if (net1.Bind(port) == 1)
			{
				cout << "Unable to bind to port " << port << endl;
				return 0;
			}

			if (net1.Listen() == 1)
			{
				cout << "Unable to listen on port " << port << endl;
				return 0;
			}

			cout << "Waiting for client connection..." << endl;
			
			if (net1.Accept(net2) == 1)
			{
				cout << "Unable to accept new connections." << endl;
				return 0;
			}

			p1Name = name;

			char tempName[15];
			strcpy(tempName, "               ");

			net1.Send(net2, (void *)p1Name.c_str(), p1Name.length());
			net1.Receive(net2, tempName, 15);

			for (int x = 0; x < 15; x++)
			{
				p2Name += tempName[x];
				if (tempName[x + 1] == ' ')
					break;
			}

			cout << endl;
			cout << "You are now ready to play against " << p2Name.c_str() << "!" << endl;
			newgetch();
		

			// by this point, we are connected to client computer

			break;

		}
		else if (menuChoice == '3')
		{
			// setup client
			clrscr();

			host = false;
			int port = 0;
			apstring name;
			apstring ip;

			cout << "You are going to be a CLIENT for this game." << endl;
			cout << endl;
			cout << "Please enter you name: ";
			cin >> name;

			cout << "Please enter the IP address to connect to: ";
			cin >> ip;

			cout << "Please enter the port to connect on: ";
			cin >> port;

			if (net1.Bind(port) == 1)
			{
				cout << "Unable to bind to port " << port << endl;
				return 0;
			}

			cout << "Attemping to connect to " << ip.c_str() << endl;

			if (net1.Connect(ip.c_str(), port) == 1)
			{
				cout << "Unable to connect to " << ip.c_str() << " on port " << port << endl;
				return 0;
			}

			// by this point, we are connected to host

			p1Name = name;
			char tempName[15];
			strcpy(tempName, "               ");

			net1.Receive(tempName, 15);
			net1.Send((void *)p1Name.c_str(), p1Name.length());
			
			for (int x = 0; x < 15; x++)
			{
				p2Name += tempName[x];
				if (tempName[x + 1] == ' ')
					break;
			}

			cout << endl;
			cout << "You are now ready to play against " << p2Name.c_str() << "!" << endl;
			newgetch();
		
			break;
		}
		else if (menuChoice == '4')
		{
			return 0;
		}
	}
 
	// play game here :)
	clrscr();
	g.myShips = PlaceShips();

	// host sends first
	// client second second
	setBackColor(0);
	clrscr();

	if (host == true)
	{
		// DISPLAY MESSAGE HERE THAT TELLS USER WE ARE WAITING TO SEND
		
		char sendMatrix[10 * 10];
		char recvMatrix[10 * 10];
		int spotCount = 0;

		// convert matrix to char
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				sendMatrix[spotCount] = g.myShips[x][y];
				spotCount++;
			}
		}

		cout << "Waiting for " << p2Name.c_str() << " to finish design his/her board..." << endl;
		
		// matrix is sendable now
		net1.Send(net2, sendMatrix, sizeof(sendMatrix));

		net1.Receive(net2, recvMatrix, sizeof(recvMatrix));

		spotCount = 0;

		// convert char to matrix
		for (x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				g.otherShips[x][y] = recvMatrix[spotCount];
				spotCount++;
			}
		}

		cout << "Send Complete!" << endl;
	}
	else // client
	{
		// MESSAGE HERE TELLING USER WAITING TO RECIEVE
		

		char sendMatrix[10 * 10];
		char recvMatrix[10 * 10];
		int spotCount = 0;

		// convert matrix to char
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				sendMatrix[spotCount] = g.myShips[x][y];
				spotCount++;
			}
		}

		cout << "Waiting for " << p2Name.c_str() << " to finish his/her board..." << endl;
		net1.Receive(recvMatrix, sizeof(recvMatrix));
		// matrix is sendable now
		net1.Send(sendMatrix, sizeof(sendMatrix));

		spotCount = 0;

		// convert char to matrix
		for (x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				g.otherShips[x][y] = recvMatrix[spotCount];
				spotCount++;
			}
		}

		cout << "Send completed!" << endl;
	}

	clrscr();
	setBackColor(0);

	int turn = 0; // let's make P1 = 1 and P2 = 2

	if (host == true)
		turn = 1;
	else
		turn = 2;

	char row = '\0';
	char col = '\0';

	while(true)
	{
		// if it's our turn.. make logical move
		if (turn == 1)
		{
			while(true)
			{
				Draw();

				int sink = checkSink(p1ShipsSunk, p2ShipsSunk);

				if (sink > 0 && sink < 5)
				{
					char textCopy[75];

					switch(sink)
					{
					case 0:
						{
							sprintf(textCopy, "%s has sunken your Battleship!", p2Name.c_str());
						} break;
					case 1:
						{
							sprintf(textCopy, "%s has sunken your Aircraft Carrier!", p2Name.c_str());
						} break;
					case 2:
						{
							sprintf(textCopy, "%s has sunken your Submarine!", p2Name.c_str());
						} break;
					case 3:
						{
							sprintf(textCopy, "%s has sunken your Cruiser!", p2Name.c_str());
						} break;
					case 4:
						{
							sprintf(textCopy, "%s has sunken your Destroyer!", p2Name.c_str());
						} break;
					}

					boxMessage(textCopy, RED, BLACK);
					clrscr();
					Draw();
				}
					
				Move(row, col);
				if (isTaken(g.myGuesses, row, col) == true)
					continue;
				else
				{
					// send move to opponent
					char sendMove[2];
					sendMove[0] = row;
					sendMove[1] = col;
					if (host == true)
						net1.Send(net2, sendMove, sizeof(sendMove));
					else
						net1.Send(sendMove, sizeof(sendMove));
				}
				// process
				processMyMove(row, col);
				break;
			}
		}
		else
			// if it's NOT our turn.. wait for move
		{
			Draw();
			
			int sink = checkSink(p1ShipsSunk, p2ShipsSunk);
			
			if (sink > 5)
			{
				char textCopy[75];
				
				switch(sink)
				{
				case 5:
					{
						sprintf(textCopy, "You sank %s's Battleship!", p2Name.c_str());
					} break;
				case 6:
					{
						sprintf(textCopy, "You sank %s's Aircraft Carrier!", p2Name.c_str());
					} break;
				case 7:
					{
						sprintf(textCopy, "You sank %s's Submarine!", p2Name.c_str());
					} break;
				case 8:
					{
						sprintf(textCopy, "You sank %s's Cruiser!", p2Name.c_str());
					} break;
				case 9:
					{
						sprintf(textCopy, "You sank %s's Destroyer!", p2Name.c_str());
					} break;
				}
				
				boxMessage(textCopy, RED, BLACK);
				clrscr();
				Draw();
			}
			
			char recvMove[2];
			
			gotoxy(5,23);
			cout << "Waiting for " << p2Name.c_str() << " to move... " << flush;

			if (host == true)
				net1.Receive(net2, recvMove, sizeof(recvMove));
			else
				net1.Receive(recvMove, sizeof(recvMove));

			row = recvMove[0];
			col = recvMove[1];

			// process
			processMove(row, col);
		}
		// check for win
		if(checkWin() == true)
			end(1);
		// check for lose
		if(checkLose() == true)
			end(2);

		if (turn == 1)
			turn = 2;
		else
			turn = 1;

	}

	return 0;
}

int checkSink(bool list[5], bool list2[5])
{
	// check my ships
	for(int x = 0; x < 5; x++)
	{
		if (g.myShipsLeft[x] == 0 && list[x] == false)
		{
			list[x] = true;
			return x;
		}
	}

	for(x = 0; x < 5; x++)
	{
		if (g.otherShipsLeft[x] == 0 && list2[x] == false)
		{
			list2[x] = true;
			return x + 5;
		}
	}

	return -1;
}


bool checkWin()
{
	int count = 0;

	for(int x = 0; x < 10; x++)
		for(int y = 0; y < 10; y++)
			if(g.myGuesses[x][y] == 2)
				count++;

	if(count == 17)
		return true;
	else
		return false;
}

bool checkLose()
{
	int count = 0;

	for(int x = 0; x < 10; x++)
		for(int y = 0; y < 10; y++)
			if(g.otherGuesses[x][y] == 2)
				count++;

	if(count == 17)
		return true;
	else
		return false;
}

void end(int temp)
{
	clrscr();

	if(temp == 1)
	{
		for(int x = 0; x < 30; x++)
		{
			gotoxy(rand() % 70, rand()%23);
			setForeColor(rand()%16);
			cout << "You Won!" << flush;
			Sleep(100);
		}
	}
	else if(temp == 2)
	{
		for(int x = 0; x < 30; x++)
		{	
			gotoxy(rand()%65, rand()%23);
			setForeColor(rand()%16);
			cout << "You Lost!" << flush;
			Sleep(100);
		}
	}
	gotoxy(0, 23);
	getch();
	exit(0);
}

void TitleScreen()
{
	setForeColor(BLACK);
	setBackColor(WHITE);
	clrscr();
	cout << endl
		 << " ******************************************************************************" << endl
		 << " *                                                                            *" << endl;
	setForeColor(RED);
	cout << " *               __ )        |   |   |       ___|  |    _)                    *" << endl
		 << " *               __ \\   _` | __| __| |  _ \\\\___ \\  __ \\  | __ \\               *" << endl
		 << " *               |   | (   | |   |   |  __/      | | | | | |   |              *" << endl
		 << " *              ____/ \\__,_|\\__|\\__|_|\\___|_____/ _| |_|_| .__/               *" << endl
		 << " *                                                        _|                  *" << endl;
	setForeColor(BLACK);
	cout << " *              Kevin Griffin                                                 *" << endl
		 << " *                                Jared Shields                               *" << endl
		 << " *                                                  Matt Kruciak              *" << endl
		 << " *                                     _==|                                   *" << endl
		 << " *                                _==|   )__)  |                              *" << endl
		 << " *                                  )_)  )___) ))                             *" << endl
		 << " *                                 )___) )____))_)                            *" << endl
		 << " *                                 )___) )____))_)                            *" << endl
		 << " *                            _    )____)_____))__)\\                          *" << endl
		 << " *                             \\---__|____/|___|___-\\\\---                     *" << endl
		 << " *" << flush;
	setForeColor(BLUE);
	cout << "                     ^^^^^^^^^" << flush;
	setForeColor(BLACK);
	cout << "\\   oo oo oo oo     /" << flush;
	setForeColor(BLUE);
	cout << "~~^^^^^^^                " << flush;
	cout << '*' << endl
		 << " *                       ~^^^^ ~~~~^^~~~~^^~~^^~~~~~                          *" << endl
		 << " *                         ~~^^      ~^^~     ~^~ ~^ ~^                       *" << endl
		 << " *                              ~^~~        ~~~^^~                            *" << endl
		 << " *                                                                            *" << endl;
	setForeColor(BLACK);
	cout << " ******************************************************************************" << endl;

	setForeColor(BLACK);
	for(int x = 3; x < 8; x++)
	{
		gotoxy(1, x);
		cout << '*' << flush;
		gotoxy(78, x);
		cout << '*' << flush;
	}

	for(x = 18; x < 23; x++)
	{
		gotoxy(1, x);
		cout << '*' << flush;
		gotoxy(78, x);
		cout << '*' << flush;
	}
	Sleep(3000);
	setBackColor(BLACK);
	setForeColor(WHITE);
	clrscr();
}
