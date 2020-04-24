#include <iostream.h>
#include <windows.h>
#include "b:\jared shields\utils.h"

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
	cout << " *              Kevin Giffin                                                  *" << endl
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

int main()
{
	TitleScreen();
	return 0;
}