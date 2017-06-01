/***************************************************************************\
	Project name: Sokoban
	Release version: 1.0
	Programmers: Nishit Vashi,  Jatin Patel, Joel M. Pinto
	Created: 09-10-2011 06:42 pm
	Completed: 26-12-2011 11:33 pm
	About: This C++ project aims to replicate the popular classic puzzle
		game Sokoban.

		[From Wikipedia - http://en.wikipedia.org/wiki/Sokoban]
		Sokoban is a type of transport puzzle, in which the player pushes
		boxes or crates around in a warehouse, trying to get them to storage
		locations. Sokoban was created in 1981 by Hiroyuki Imabayashi, and
		published in 1982 by Thinking Rabbit, a software house based in
		Takarazuka, Japan.

		Rules:
			1. Only one box can be pushed at a time.
			2. A box cannot be pulled.
			3. The player cannot walk through boxes or walls.
			4. The puzzle is solved when all boxes are located at storage locations.
	Program files:
		Sokoban.cpp	- Contains main()
		Map.cpp		- Handles navigation in a level
		Image.cpp	- Handles sprites (images)
		ImageLdr.cpp- Image Loader; Handles loading sprites for cells
		Keybrd.cpp	- Encapsulates Keyboard input
		LevelSys.cpp- Level System; Handles loading levels
		GameEng.cpp	- The game engine for Sokoban
		MainMenu.cpp- Main Menu for the game
\***************************************************************************/

//Include libraries
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

//Include code files
#include "C:\SOKOBAN\mainmenu.cpp"
#include "C:\SOKOBAN\gameeng.cpp"

//Main body of program
int main()
{
	//Initialize graphics mode
	int gdriver=DETECT, gmode;
	initgraph(&gdriver, &gmode, "..\\BGI");

	int errorcode=graphresult();
	if (errorcode!=grOk)
	{
		cout<<"Could not load graphics mode\n\n"
			<<"Error Description: "<<grapherrormsg(errorcode)
			<<"\nExiting...";
		getch();
		return 1;
	}

	//Show the Main Menu
	while(1)
	{
		switch(Main_Menu::show()) //Check the user's choice
		{
			case 1: //Play
				Game_Engine ge;
				ge.start();
				break;
			case 2: //About
				Main_Menu::display_about();
				break;
			case 3: //Help
				Main_Menu::display_help();
				break;
			case 4: //Tutorials
				Game_Engine tut("C:\\sokoban\\levels\\tut",5);
				tut.start();
				break;
			case 5: //Exit
				//Show a confirmation dialog
				if (!Main_Menu::confirm_exit()) break;
				closegraph(); //Go back to text mode
				return 0;
		}
	}
}
