/*
	ImageLdr.cpp - Image Loader; Handles loading sprites for cells
	Part of the Sokoban project
	(See Sokoban.cpp for details)
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef IMAGELDR_CPP
#define IMAGELDR_CPP

#include "C:\sokoban\IMAGE.CPP"

class Image_Loader
{
public:
	Image Empty;
	Image Wall;
	Image Box;
	Image Target;
	Image Player;

	//Constructor
	Image_Loader()
	{
		Empty.load_from_file("C:\\sokoban\\sprites\\empty.raw");
		Wall.load_from_file("C:\\sokoban\\sprites\\wall.raw");
		Box.load_from_file("C:\\sokoban\\sprites\\box.raw");
		Target.load_from_file("C:\\sokoban\\sprites\\target.raw");
		Player.load_from_file("C:\\sokoban\\sprites\\player.raw");
	}

}il;
#endif //IMAGELDR.CPP