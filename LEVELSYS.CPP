/*
	LevelSys.cpp - Level System; Handles loading levels
	Part of the Sokoban project
	(See Sokoban.cpp for details)
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef LEVELSYS_CPP
#define LEVELSYS_CPP

#include<string.h>
#include<stdlib.h>
#include"C:\SOKOBAN\Map.cpp"

class Level_System
{
private:
	int curr_level;
	char *level_path;
	int max_levels;
	Map *m;
public:
	Level_System() : level_path("C:\\sokoban\\levels\\level")
	{
		curr_level=1;
		max_levels=155;
		m=NULL;
	}

	Level_System(char *path, int maxlvls)
	{
		strcpy(level_path,path);
		curr_level=1;
		max_levels=maxlvls;
		m=NULL;
	}

	void load_level(Map *, int); //Loads (level_no)th level into map
	void change_level(int); //Changes the level by delta(-1,0 or +1)

};

//Loads (level_no)th level into map
void Level_System::load_level(Map *map,int level_no)
{
	m=map;
	char path[80]="";
	strcpy(path,level_path);
	char strlno[5]=""; //string which stores level_no
	itoa(level_no,strlno,10); //store level_no in strlno
	strcat(path,strlno);
	strcat(path,".dat");

	cleardevice();
	setfillstyle(SOLID_FILL,WHITE);
	floodfill(1,1,WHITE);
	if(m->load_from_file(path)) //Returns 1 on error else 0
	{
		//error occurred
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(320,240,"File Error: Could not load level");
	}
	curr_level=level_no;

	char strout[20]="Level ";
	strcat(strout,strlno);
	settextjustify(RIGHT_TEXT,TOP_TEXT);
	outtextxy(639,0,strout);
	m->show_num_moves();

	//Write help strings if tutorials are being played
	char *tut[] = { "Press the right arrow key to push the box into the target.",
		"Good, now try to push these 2 boxes into those targets.",
		"Great! Try this now. TIP: Press [R] to reset a level.",
		"Another TIP: Press [P]/[N] for navigating to a previous/next level respectively.",
		"This is the last one. TIP: Press [Q]/[Esc] to go back to the main menu."};
	if (strstr(level_path,"tut")) //will return non-zero if "tut" found in path
	{
		settextjustify(LEFT_TEXT,TOP_TEXT);
		setcolor(BLACK);
		outtextxy(20,400,tut[level_no-1]);
	}
}

//Changes the level by delta(-1,0 or +1)
void Level_System::change_level(int delta)
{
	int new_level;

	if(delta==0)
	{
		new_level=curr_level;
	}
	else if(delta==1)
	{
		if(curr_level==max_levels)
			new_level=1;
		else
			new_level=curr_level+1;
	}
	else if(delta==-1)
	{
		if(curr_level==1)
			new_level=max_levels;
		else
			new_level=curr_level-1;
	}
	else //Invalid argument
	{
		return ; //to prevent undefined behaviour
		//Assume delta to be either -1, 0 or 1.
	}
	load_level(m,new_level);
}
#endif //LEVELSYS_CPP