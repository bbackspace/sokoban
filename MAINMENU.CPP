/*
	MainMenu.cpp - Main Menu for the game
	Part of the Sokoban project
	(See Sokoban.cpp for details)
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef MAINMENU_CPP
#define MAINMENU_CPP

#include<graphics.h>
#include<dos.h>

#include"C:\SOKOBAN\map.cpp"
#include"C:\SOKOBAN\keybrd.cpp"
#include"C:\SOKOBAN\imageldr.cpp"
class Main_Menu
{
public:
	static int show(); //Shows the Main Menu and returns the user's choice
	static void display_help(); //Shows the Help screen
	static void display_about(); //Shows the About screen
	static int confirm_exit(); //Shows an exit confirmation dialog

};

//Shows the Main Menu and returns the user's choice
int Main_Menu::show()
{
	cleardevice();
	setfillstyle(SOLID_FILL,WHITE);
	floodfill(1,1,WHITE);

	//---------------------SOKOBAN TITLE--------
	setcolor(BLACK);
	char *strheading="Sokoban";
	settextstyle(9, HORIZ_DIR, 0);
	setusercharsize(4, 3, 4, 3);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	outtextxy(15,0,strheading);

	int h=textheight(strheading)+10;
	int w=textwidth(strheading);
	line(0,h,20+w,h);

	//Serifs
	line(15+w,h,20+w,h+5);
	line(20+w,h,25+w,h+5);

	//---------------------MAIN MENU TITLE------
	char *strmenu="Main Menu";
	settextstyle(9, HORIZ_DIR, 0);
	setusercharsize(1, 2, 1, 2);
	settextjustify(RIGHT_TEXT,TOP_TEXT);
	outtextxy(630,60,strmenu);
	h=textheight(strmenu)+70;
	w=textwidth(strmenu);
	line(640,h,640-w-20,h);

	//Serifs
	line(640-w-15,h,640-w-20,h+5);
	line(640-w-20,h,640-w-25,h+5);

	//---------------------OPTION LABELS--------
	//Calculate offset of label position from center
	int off=(7*SPR_WIDTH)/2 + 5;
	//7=no of cells horizontally&vertically, 5=margin
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(9, HORIZ_DIR, 0);
	setusercharsize(1, 3, 1, 3);
	outtextxy(320,240-off-textheight("Play")/2,"Play");
	outtextxy(320-off-textwidth("Tutorial")/2,240,"Tutorial");
	outtextxy(320+off+textwidth("About")/2,240,"About");
	outtextxy(320,240+off+textheight("Exit")/2,"Exit");

	//---------------------INSTRUCTIONS---------
	settextjustify(CENTER_TEXT,TOP_TEXT);
	settextstyle(9, HORIZ_DIR, 0);
	setusercharsize(1, 3, 1, 3);
	h=textheight("T")+5;//5=line spacing
	outtextxy(320,480-2*h,"To select a menu option, push in that direction");
	outtextxy(320,480-h,"Press F1 for Help");

	//---------------------MENU OPTIONS---------
	Map menu;
	menu.load_from_file("C:\\sokoban\\levels\\mainmenu.dat");
	while(1)
	{
		if(Keyboard::check_key())
		switch(Keyboard::read_key())
		{
			case (KEY_F1):
				return 3;
			case (KEY_UP): //Play
				menu.try_move('y',-1,0);
				delay(500);
				return 1;
			case (KEY_LEFT): //Tutorials
				menu.try_move('x',-1,0);
				delay(500);
				return 4;
			case (KEY_RIGHT): //About
				menu.try_move('x',+1,0);
				delay(500);
				return 2;
			case (KEY_DOWN): //Exit
				menu.try_move('y',+1,0);
				delay(500);
				//deliberate fall-through
			case (KEY_Q):
			case (KEY_ESC): return 5; //Exit
		}
	}
}

//Shows the Help screen
void Main_Menu::display_help()
{
	cleardevice();
	char *strhelp="Help";
	setfillstyle(SOLID_FILL,WHITE);
	floodfill(1,1,WHITE);
	setcolor(BLACK);
	settextstyle(9,HORIZ_DIR,0);
	setusercharsize(1,2,1,2);
	settextjustify(RIGHT_TEXT,TOP_TEXT);
	outtextxy(630,10,strhelp);

	int h=textheight(strhelp)+20; //help string underline height
	int w=textwidth(strhelp); //help string width
	line(640,h,640-w-20,h);

	//Serifs
	line(640-w-15,h,640-w-20,h+5);
	line(640-w-20,h,640-w-25,h+5);

	h=50+textheight(strhelp);
	line(320,h,320,480-30);
	setusercharsize(1,3,1,3);
	outtextxy(640/4,h,"How to Play");
	outtextxy(640-640/4,h,"Controls");

	//How to play
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setusercharsize(1,3,1,4);
	h+=textheight("H")+20;
	il.Player.display(16,h,-1);
	outtextxy(48,h,"®-This is the player");
	il.Box.display(16,h+32,-1);
	outtextxy(48,h+32,"®-This is a box");
	il.Wall.display(16,h+64,-1);
	outtextxy(48,h+64,"®-This is a wall");
	il.Target.display(16,h+96,-1);
	outtextxy(48,h+96,"®-This is a target space");
	char line1[]="Aim: You need to move all boxes to";
	char line2[]="     the target spaces.";
	char line3[]="Rules:";
	char line4[]="1 Only one box can be pushed at a";
	char line5[]="  time.";
	char line6[]="2 A box cannot be pulled.";
	char line7[]="3 The player cannot walk through";
	char line8[]="  boxes or walls.";
	char line9[]="4 The puzzle is solved when all";
	char line10[]="  boxes are located at targets";
	outtextxy(16,h+128,line1);
	outtextxy(16,h+144,line2);
	outtextxy(16,h+176,line3);
	outtextxy(16,h+192,line4);
	outtextxy(16,h+208,line5);
	outtextxy(16,h+224,line6);
	outtextxy(16,h+240,line7);
	outtextxy(16,h+256,line8);
	outtextxy(16,h+272,line9);
	outtextxy(16,h+288,line10);

	//Controls
	w=320+16;
	outtextxy(w,h,"Arrow keys to move/push");
	outtextxy(w,h+32,"P = Previous level");
	outtextxy(w,h+64,"N = Next level");
	outtextxy(w,h+96,"R = Reset level");
	outtextxy(w,h+128,"Q / Esc = Quit to Main Menu");

	while (!Keyboard::check_key()) ;
	Keyboard::read_key();
}

//Shows the About screen
void Main_Menu::display_about()
{
	cleardevice();
	setfillstyle(SOLID_FILL,LIGHTCYAN);
	floodfill(1,1,LIGHTCYAN);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(9,HORIZ_DIR,0);
	setusercharsize(6,10,6,10);
	outtextxy(320,40,"Sokoban");
	setusercharsize(3,8,3,8);
	settextjustify(CENTER_TEXT,TOP_TEXT);
	int h=textheight("A")+5;
	outtextxy(320,90,"Version 1.0. Coded by:");
	outtextxy(320,90+h,"Jatin Patel,Joel Pinto and Nishit Vashi");

	char *lines[]={
		" Sokoban is a type of transport puzzle which was created in 1981",
		" by Hiroyuki Imabayashi. This project aims to replicate this puzzle.",
		" Microban Levels by David W. Skinner (155 Microban levels)",
		" http://users.bentonrea.com/~sasquatch/sokoban/",
		" Tutorial levels by Joel"
	};
	for(int i=0;i<5;++i)
	{
		outtextxy(320,90+h*(i+2),lines[i]);
	}
	while (!Keyboard::check_key()) ;
	Keyboard::read_key();
}

//Shows a confirmation dialog at the time of exit
int Main_Menu::confirm_exit()
{
	char *str=" Are you sure you want to exit?";
	const int dialogw=textwidth(str)+40; //Dialog box width
	const int dialogh=2*textheight(str)+60; //Dialog box height
	setfillstyle(SOLID_FILL,LIGHTCYAN);
	bar(320-dialogw/2,240-dialogh/2,320+dialogw/2,240+dialogh/2);
	settextjustify(CENTER_TEXT,TOP_TEXT);
	outtextxy(320,240-dialogh/2+20,str);
	str="Y=Yes, N=No";
	outtextxy(320,240-dialogh/2+40+textheight(str),str);
	while(1)
	{
		if(Keyboard::check_key())
		switch(Keyboard::read_key())
		{
			case (KEY_N): return 0;
			case (KEY_Y): return 1;
		}
	}
}
#endif //MAINMENU_CPP
