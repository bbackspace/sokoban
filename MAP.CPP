/*
	Map.cpp - Handles navigation in a level
	Part of the Sokoban project
	(See Sokoban.cpp for details)
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef MAP_CPP
#define MAP_CPP

#include<fstream.h>
#include<stdio.h>
//#include<conio.h> //For purpose of debugging

#include "C:\sokoban\imageldr.cpp"
//map data - possible cell values
const int c_empty=0;
const int c_wall=1;
const int c_box=2;
const int c_target=4;
const int c_player=8;

//Map class and function declarations
class Map
{
private:
//public: //For purpose of debugging
	int r; //no. of rows in the cell grid
	int c; //no. of columns in the cell grid
	int grid[30][40]; //max 30 rows by 40 columns - stores the grid data
	int plrx; //x-coordinate of player position
	int plry; //y-coordinate of player position
	int no_of_moves;

	void move_plr_to(int, int, int); //Move player to position (x,y)
public:
	int get_cell(int, int); //Accessor for cell type at (x,y)
	void set_cell(int, int, int); //Sets the cell type at (x,y) with 'cell'

	Map(); //Constructor

	int load_from_file(char *); //Loads the current instance from a file
	int save_to_file(char *); //Saves the current instance to a file

	int num_rows() { return r; } //Accessor for number of rows
	int num_cols() { return c; } //Accessor for number of columns
	void num_rows(int _r) { if (_r>0&&_r<=30) r=_r; }
	void num_cols(int _c) { if (_c>0&&_c<=40) c=_c; }
	int player_x() { return plrx; } //Accessor for player position (x)
	int player_y() { return plry; } //Accessor for player position (y)
	void player_x(int x) { if(x>0&&x<c) plrx=x; }
	void player_y(int y) { if(y>0&&y<r) plry=y; }
	int num_moves() { return no_of_moves; }

	void try_move(char, int, int =1); //Try to move player on 'axis' by 'offset' cells

	int check_win(); //Check if the level has been completed
	void update_image(int, int); //Updates the image of the cell at (x,y)
	void show_num_moves();
};

//function definitions

//Constructor
Map::Map()
{
	//Initialize everything with valid data
	r=30;
	c=40;
	for(int i=0;i<30;++i)
		for(int j=0;j<40;++j)
			grid[i][j]=0;
	plrx=plry=0;
	no_of_moves=0;
}

//Accessor for cell type at (x,y)
int Map::get_cell(int x, int y)
{
	return grid[y][x]; //Row=y, Column=x
}

//Sets the cell type at (x,y) with 'cell'
void Map::set_cell(int x, int y, int cell)
{
	if (x<0||x>=c || y<0||y>=r)
		return; //Cell coordinates out of range, so reject

	if (cell>=0&&cell<=12) //12 is max possible cell value
		grid[y][x]=cell;
}

//Loads the current instance from a file. Returns 1 if error encountered.
int Map::load_from_file(char *path)
{
	ifstream level;
	level.open(path,ios::in,ios::binary);
	if (!level) return 1; //Error in file opening
	if(!level.read((char *)this,sizeof(Map))) //Store in current instance
	{
		level.close();
		return 1; //Error while reading
	}
	level.close();
	for(int x=0;x<c;++x)
		for(int y=0;y<r;++y)
			update_image(x,y);
	return 0;
}

//Saves the current instance to a file. Returns 1 if error encountered.
int Map::save_to_file(char *path)
{
	ofstream level;
	level.open(path,ios::out,ios::binary);
	if (!level) return 1; //Error in file creation
	level.seekp(0,ios::beg);
	level.write((char *)this,sizeof(Map)); //Write the current instance
	level.close();
	//return level.tellp();
	return 0;
}
//Try to move player on 'axis' by 'offset' cells
void Map::try_move(char axis, int offset, int showmoves)
{
	//adj1 = 1st adjacent cell in the direction the player wants to move
	//adj2 = cell adjacent to 1st adjacent cell

	int adj1_x,adj1_y,adj2_x,adj2_y; //cell position coordinates
	int adj1_cell,adj2_cell; //cell types
	if(axis=='x'||axis=='X')
	{
		adj1_x=plrx+offset;
		adj1_y=plry;
		adj2_x=adj1_x+offset;
		adj2_y=adj1_y;
	}
	else if(axis=='y'||axis=='Y')
	{
		adj1_x=plrx;
		adj1_y=plry+offset;
		adj2_x=adj1_x;
		adj2_y=adj1_y+offset;
	}
	adj1_cell=get_cell(adj1_x,adj1_y);

	if (adj1_cell==c_empty||adj1_cell==c_target)
		move_plr_to(adj1_x,adj1_y,showmoves);
	else if (adj1_cell==c_wall)
		return ; //cannot push wall
	else if (adj1_cell&c_box) //cell has box (with or without target)
	{
		adj2_cell=get_cell(adj2_x,adj2_y);
		if(adj2_cell&c_wall || adj2_cell&c_box)
			return ; //cannot push coz box is against a wall or another box
		else //Box is pushable
		{
			//Add box to adj2
			set_cell(adj2_x,adj2_y,adj2_cell|c_box);
			update_image(adj2_x,adj2_y);

			//Remove box from adj1
			set_cell(adj1_x,adj1_y,adj1_cell&(~c_box));
			//Move player to adj1
			move_plr_to(adj1_x,adj1_y,showmoves);
		}
	}
}

//Move player to position (x,y)
//if showmoves!=0, number of moves will be shown
void Map::move_plr_to(int x, int y, int showmoves)
{
	//Remove player from old cell (plrx,plry)
	int playercell=get_cell(plrx,plry);
	set_cell(plrx,plry,(playercell&(~c_player)));
	update_image(plrx,plry);
	//Send player to new cell (x,y)
	playercell=get_cell(x,y);
	set_cell(x,y,(playercell|c_player));
	update_image(x,y);
	plrx=x;
	plry=y;
	no_of_moves++;
	if(showmoves)
	show_num_moves();
}

//Shows the number of moves on the screen
void Map::show_num_moves()
{
	char strmoves[20]="";
	sprintf(strmoves,"Moves - %d",no_of_moves);
	//erase old label
	setfillstyle(SOLID_FILL,WHITE);
	bar(640,textheight("Level")+20,640-textwidth("Moves - XXX"),2*textheight("Level")+20);
	//display new label
	settextjustify(RIGHT_TEXT,TOP_TEXT);
	outtextxy(640,textheight("Level")+20,strmoves);
}

//Check if the level has been completed
int Map::check_win()
{
	for(int i=0;i<r;++i)
		for(int j=0;j<c;++j)
			if(get_cell(j,i)&c_target)
				if((get_cell(j,i)&c_box)==0)
					return 0;
	return 1;
}

//Updates the image of the cell at (x,y)
void Map::update_image(int x, int y)
{
	int mapx=320-(c*SPR_WIDTH)/2;
	int mapy=240-(r*SPR_HEIGHT)/2;

	int cellx=mapx+x*SPR_WIDTH;
	int celly=mapy+y*SPR_HEIGHT;
	int c=get_cell(x,y);
	if(c==c_empty)
	{
		il.Empty.display(cellx,celly,-1);
		return ;
	}
	if(c==c_wall)
	{
		il.Wall.display(cellx,celly,WHITE);
		return ;
	}
	if(c&c_target)
	{
		if (c==c_target)
			il.Target.display(cellx,celly,-1);
		else
			il.Target.display(cellx,celly,WHITE);

	}
	if(c&c_box)
	{
		il.Box.display(cellx,celly,WHITE);
		return ;
	}
	if(c&c_player)
	{
		il.Player.display(cellx,celly,WHITE);
	}
}
/*
//For purpose of debugging:
void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..\\BGI\\");
	setfillstyle(SOLID_FILL,WHITE);
	floodfill(1,1,WHITE);
	Map menu;

	menu.set_cell(0,0,c_wall);
	menu.set_cell(1,0,c_wall);
	menu.set_cell(2,0,c_wall);
	menu.set_cell(3,0,c_wall);
	menu.set_cell(4,0,c_wall);
	menu.set_cell(0,1,c_wall);
	menu.set_cell(4,1,c_wall);
	menu.set_cell(5,1,c_wall);
	menu.set_cell(7,1,c_wall);
	menu.set_cell(8,1,c_wall);
	menu.set_cell(9,1,c_wall);
	menu.set_cell(10,1,c_wall);
	menu.set_cell(0,2,c_wall);
	menu.set_cell(3,2,c_box);
	menu.set_cell(5,2,c_wall);
	menu.set_cell(6,2,c_wall);
	menu.set_cell(7,2,c_wall);
	menu.set_cell(9,2,c_target);
	menu.set_cell(10,2,c_wall);
	menu.set_cell(0,3,c_wall);
	menu.set_cell(2,3,c_box);
	menu.set_cell(6,3,c_box);
	menu.set_cell(9,3,c_target);
	menu.set_cell(10,3,c_wall);
	menu.set_cell(0,4,c_wall);
	menu.set_cell(1,4,c_wall);
	menu.set_cell(3,4,c_box);
	menu.set_cell(4,4,c_wall);
	menu.set_cell(5,4,c_wall);
	menu.set_cell(6,4,c_wall);
	menu.set_cell(7,4,c_wall);
	menu.set_cell(8,4,c_wall);
	menu.set_cell(9,4,c_target);
	menu.set_cell(10,4,c_wall);
	menu.set_cell(12,4,c_wall);
	menu.set_cell(13,4,c_wall);
	menu.set_cell(14,4,c_wall);
	menu.set_cell(15,4,c_wall);
	menu.set_cell(0,5,c_wall);
	menu.set_cell(2,5,c_box);
	menu.set_cell(5,5,c_wall);
	menu.set_cell(7,5,c_wall);
	menu.set_cell(9,5,c_target);
	menu.set_cell(10,5,c_wall);
	menu.set_cell(11,5,c_wall);
	menu.set_cell(12,5,c_wall);
	menu.set_cell(15,5,c_wall);
	menu.set_cell(0,6,c_wall);
	menu.set_cell(5,6,c_wall);
	menu.set_cell(7,6,c_wall);
	menu.set_cell(9,6,c_target);
	menu.set_cell(10,6,c_wall);
	menu.set_cell(13,6,c_player);
	menu.set_cell(15,6,c_wall);
	menu.set_cell(0,7,c_wall);
	menu.set_cell(1,7,c_wall);
	menu.set_cell(2,7,c_wall);
	menu.set_cell(5,7,c_wall);
	menu.set_cell(7,7,c_wall);
	menu.set_cell(15,7,c_wall);
	menu.set_cell(2,8,c_wall);
	menu.set_cell(3,8,c_wall);
	menu.set_cell(4,8,c_wall);
	menu.set_cell(5,8,c_wall);
	menu.set_cell(7,8,c_wall);
	menu.set_cell(8,8,c_wall);
	menu.set_cell(14,8,c_wall);
	menu.set_cell(15,8,c_wall);
	menu.set_cell(8,9,c_wall);
	menu.set_cell(9,9,c_wall);
	menu.set_cell(10,9,c_wall);
	menu.set_cell(11,9,c_wall);
	menu.set_cell(12,9,c_wall);
	menu.set_cell(13,9,c_wall);
	menu.set_cell(14,9,c_wall);
	menu.plrx=13;//13
	menu.plry=6;//6
	menu.r=10;//10
	menu.c=16;//16

	for(int x=0;x<menu.c;++x)
		for(int y=0;y<menu.r;++y)
			menu.update_image(x,y);
	//cout<<((menu.save_to_file("G:\\levels\\level98.dat"))?"Saving failed":"Saving Successful");
	cout<<menu.save_to_file("G:\\levels\\level98.dat");

	//cout<<((menu.load_from_file("G:\\levels\\level98.dat"))?"Loading failed":"Loading Successful");
	while(!menu.check_win())
	{
		switch(getch())
		{
			case 'a': menu.try_move('x',-1); break;
			case 'd': menu.try_move('x',+1); break;
			case 'w': menu.try_move('y',-1); break;
			case 's': menu.try_move('y',+1); break;
			case 'q': closegraph(); return;
		}

	}
	setcolor(BLACK);
	settextstyle(9,HORIZ_DIR,4);
	settextjustify(LEFT_TEXT,BOTTOM_TEXT);
	outtextxy(10,469,"You Win!!!");
	getch();
	closegraph();
}
*/
#endif //MAP_CPP
