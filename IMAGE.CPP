/*
	Image.cpp - Handles sprites (images)
	Part of the Sokoban project
	(See Sokoban.cpp for details)
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef IMAGE_CPP
#define IMAGE_CPP

#define SPR_HEIGHT 16 //Max height of sprites
#define SPR_WIDTH  16 //Max width of sprites

#include<graphics.h>
#include<fstream.h>
//#include<conio.h>
class Image
{
private:
	unsigned char _pixdat[SPR_HEIGHT][SPR_WIDTH]; //pixel data
public:
	void display(int, int, int);
	int load_from_file(char *); //file must be .raw file type

};

//Loads the current instance from a file. Returns 1 if error encountered.
int Image::load_from_file(char *path)
{
	ifstream imgfile;
	imgfile.open(path,ios::in|ios::binary);
	if (!imgfile) return 1; //Error in file opening

	unsigned char dat;
	for(int i=0;i<SPR_HEIGHT;++i)
		for(int j=0;j<SPR_WIDTH;++j)
		{
			//Read each byte(char) from the file
			imgfile.read((char *)&dat,sizeof(char));

			//Each byte in the RAW 4bpp format used by
			//Photoshop is 0000KBGR (K=brightness).
			//It should be converted to 0000KRGB, so
			//swap bit 0 with bit 2 i.e, red and blue
			dat=((dat&0x01)<<2)|((dat&0x04)>>2)|(dat&0x0A); //0x0A = (bin)00001010

			//0111 has to be interchanged with 1000 for correct color
			if (dat==7) dat=8;
			else if (dat==8) dat=7;

			_pixdat[i][j]=dat;
		}
	imgfile.close();
	return 0;
}

void Image::display(int x, int y, int transparency_key)
{
	for(int i=0;i<SPR_HEIGHT;++i)
		for(int j=0;j<SPR_WIDTH;++j)
		{
			if (transparency_key!=-1 && _pixdat[i][j]==transparency_key)
				continue;

			putpixel(x+j,y+i,_pixdat[i][j]);

			//Use these lines instead of putpixel to scale the image by 2x:
			//setcolor(_pixdat[i][j]);
			//rectangle(x+2*j,y+2*i,x+2*j+1,y+2*i+1);
		}
}

//main function used to test image.cpp.
//Do not uncomment if including image.cpp in other files.
/*
int main()
{
	Image img;
	if(!img.load_from_file("G:\\sprites\\box.raw"))
	cout<<"Image loaded successfully!";
	else
	{
		cout<<"Image could not be loaded";
		getch();
		return 1;
	}
	getch();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..\\BGI");

	//cleardevice();
	setfillstyle(SOLID_FILL,WHITE);
	floodfill(10,10,WHITE);
	for(int i=1;i<=40;++i)
	for(int j=1;j<=30;++j)
	{
		//if(i==1||i==40||j==1||j==30)
		img.display(16*(i-1),16*(j-1),-1);
	}
	getch();
	closegraph();
	return 0;
}
*/
#endif //IMAGE_CPP
