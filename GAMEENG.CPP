/*
	GameEng.cpp - The game engine for Sokoban
	Part of the Sokoban project
	(See Sokoban.cpp for details)
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef GAMEENG_CPP
#define GAMEENG_CPP

#include<stdio.h>
#include<dos.h>

#include "C:\SOKOBAN\keybrd.cpp"
#include "C:\SOKOBAN\levelsys.cpp"
class Game_Engine
{
private:
	Map m;
	Level_System ls;

	int input(int keycode); //Processes input from keyboard
	void win();
public:
	//Constructors
	Game_Engine()
	{	}
	Game_Engine(char *level_path,int max_levels) : ls(level_path,max_levels)
	{	}

	void start(); //Starts the Game Engine
};

//Starts the Game Engine
void Game_Engine::start()
{
	ls.load_level(&m,1);
	while(1)
	{
		if (Keyboard::check_key())
			if (input(Keyboard::read_key()) == -1)
				break; //-1 is request to exit to main menu
	}
}

//Processes input from keyboard
int Game_Engine::input(int keycode)
{
	switch(keycode)
	{
		case (KEY_UP):
			m.try_move('y',-1); //Move on y-axis one cell up
			if (m.check_win()) win();
			break;
		case (KEY_DOWN):
			m.try_move('y',+1); //Move on y-axis one cell down
			if (m.check_win()) win();
			break;
		case (KEY_LEFT):
			m.try_move('x',-1); //Move on x-axis one cell left
			if (m.check_win()) win();
			break;
		case (KEY_RIGHT):
			m.try_move('x',+1); //Move on x-axis one cell right
			if (m.check_win()) win();
			break;
		case (KEY_P): //Previous level
			ls.change_level(-1);
			break;
		case (KEY_N): //Next level
			ls.change_level(+1);
			break;
		case (KEY_R): //Reload level
			ls.change_level(0);
			break;
		case (KEY_ESC): case (KEY_Q): //Quit to main menu
			return -1;
		default: break;
	}
	return 0;
}

void Game_Engine::win()
{
	delay(200); //To prevent closing of the dialog before being seen
	char *str;
	if (m.num_moves()!=1)
		sprintf(str,"You completed this level in %d moves",m.num_moves());
	else
		sprintf(str,"You completed this level in %d move",m.num_moves());
	const int dialogw=textwidth(str)+40; //Dialog box width
	const int dialogh=2*textheight(str)+60; //Dialog box height
	setfillstyle(SOLID_FILL,LIGHTCYAN);
	bar(320-dialogw/2,240-dialogh/2,320+dialogw/2,240+dialogh/2);
	settextjustify(CENTER_TEXT,TOP_TEXT);
	outtextxy(320,240-dialogh/2+20,str);
	str="Press any key for the next level";
	outtextxy(320,240-dialogh/2+40+textheight(str),str);
	while(!Keyboard::check_key());
	Keyboard::read_key(); //dummy call to prevent unpredictable behaviour
	ls.change_level(+1);
}
#endif //GAMEENG_CPP
