/*
	Keybrd.cpp - Encapsulates Keyboard input
	Part of the Sokoban project
	(See Sokoban.cpp for details)

	Uses bioskey() function from bios.h
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef KEYBRD_CPP
#define KEYBRD_CPP

//#include<iostream.h>
//#include<conio.h>

#include<bios.h>

#define KEY_ESC 1
#define KEY_F1 59
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_ENTER 28
#define KEY_P 25
#define KEY_N 49
#define KEY_R 19
#define KEY_Q 16
#define KEY_Y 21

class Keyboard
{
public:
	static int check_key(void)
	{
		return bioskey(1);
	}
	static int read_key(void)
	{
		return bioskey(0)>>8;
	}
};

//main function used to test keybrd.cpp.
//Do not uncomment if including keybrd.cpp in other files.
/*
void main()
{
	clrscr();
	Keyboard kb;
	float a=1.0, inc=0;
	gotoxy(1,20);
	cprintf("Press UP/DOWN to adjust the rate of change of the no. ESC to exit.");
	gotoxy(1,1);
	while(1)
	{
		if (kb.check_key())
		{
			switch(kb.read_key())
			{
				case (KEY_UP): inc+=0.1; break;
				case (KEY_DOWN): inc-=0.1; break;
				case (KEY_ESC): return;
			}
		}
		a+=inc;
		cprintf("%f         \r",a);
	}
}
*/
#endif //KEYBRD_CPP