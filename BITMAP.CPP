/*
	Bitmap.cpp - Saves a screenshot of the current state in graphics mode
	as a 4bpp 640x480 BMP.
*/

// The following if condition prevents accidental
// double inclusion in other files.
#ifndef BITMAP_CPP
#define BITMAP_CPP

#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

//Bitmap class and function declarations
class Bitmap
{
private:
	// BitMap File Header
	byte bfType[2]; // 1 2 must always be set to `BM' to declare that this is a .bmp file.
	dword bfSize; // 3 4 specifies the size of the file in bytes.
	word bfReserved1;// 7 2 must always set to zero.
	word bfReserved2;// 9 2 must always be set to zero.
	dword bfOffset; // 11 4 specifies the offset from the beginning of the file to bitmap data.

	// BitMap Image Header
	dword biSize; // 15 4 specifies the size of the BitMap Header structure, in bytes.
	dword biWidth; // 19 4 specifies the width of image, in pixels.
	dword biHeight; // 23 4 specifies the height of image, in pixels.
	word biPlanes; // 27 2 specifies the number of planes of the target device,must be set to 0
	word biBitCount; // 29 2 specifies the number of bits per pixel.
	dword biCompression; //31 4 Specifies the type of compression, usually set to 0 - No Compres
	dword biSizeImage; // 35 4 specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
	dword biXPelsPerMeter; //39 4 specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.
	dword biYPelsPerMeter; // 43 4 specifies the the vertical pixels per meter on the designated targer device, usually set to zero
	dword biClrUsed; // 47 4 specifies the number of colors used in bitmap, if set to 0 number of colors is calculated using the biBitCount member.
	dword biClrImportant; // 51 4 specifies the number of color that are `important' for the bitmap, if set to zero, all colors are important.

public:
	int SaveBMP16(char []);
};

int Bitmap::SaveBMP16(char file[])
{
	int i=0, j=0, r, g, b;

	FILE *fp;
	Bitmap *bmp;

	bmp=(Bitmap *)malloc(54);

	bmp->bfType[0]='B';
	bmp->bfType[1]='M';
	bmp->bfSize=153718;
	bmp->bfReserved1=0;
	bmp->bfReserved2=0;
	bmp->bfOffset=118;
	bmp->biSize=40;
	bmp->biWidth=640;
	bmp->biHeight=480;
	bmp->biPlanes=1;
	bmp->biBitCount=4;
	bmp->biCompression=0;
	bmp->biSizeImage=153600; //Fixed Size = 640 x 480 / 2 (1 byte=2pixels)
	bmp->biXPelsPerMeter=0;
	bmp->biYPelsPerMeter=0;
	bmp->biClrUsed=0;
	bmp->biClrImportant=0;

	fp=fopen(file, "wb");
	if(fp == NULL)
	{
		return 1;
	}

	fwrite(bmp, 54, 1, fp);
	fseek(fp, 54L, SEEK_SET);

	fputc(0x0, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(127, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(0x0, fp);
	fputc(127, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(127, fp);
	fputc(127, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(0x0, fp);
	fputc(0x0, fp);
	fputc(127, fp);
	fputc(0x0, fp);

	fputc(127, fp);
	fputc(0x0, fp);
	fputc(127, fp);
	fputc(0x0, fp);

	fputc(0x0, fp);
	fputc(192, fp);
	fputc(192, fp);
	fputc(0x0, fp);

	fputc(192, fp);
	fputc(192, fp);
	fputc(192, fp);
	fputc(0x0, fp);

	fputc(128, fp);
	fputc(128, fp);
	fputc(128, fp);
	fputc(0x0, fp);

	fputc(255, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(0x0, fp);
	fputc(255, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(255, fp);
	fputc(255, fp);
	fputc(0x0, fp);
	fputc(0x0, fp);

	fputc(0x0, fp);
	fputc(0x0, fp);
	fputc(255, fp);
	fputc(0x0, fp);

	fputc(255, fp);
	fputc(0x0, fp);
	fputc(255, fp);
	fputc(0x0, fp);

	fputc(0x0, fp);
	fputc(255, fp);
	fputc(255, fp);
	fputc(0x0, fp);

	fputc(255, fp);
	fputc(255, fp);
	fputc(255, fp);
	fputc(0x0, fp);

	i=0;
	j=479;

	fseek(fp, 118, SEEK_SET);

	while(j>=0)
	{
		i=0;
		while(i<640)
		{
			fputc((getpixel(i, j)<<4) | getpixel(i+1, j), fp);
			i+=2;
		}
		j--;
	}
	free(bmp);
	fclose(fp);
	return 0;
}

#endif //BITMAP_CPP