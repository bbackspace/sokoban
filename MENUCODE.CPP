
#include <graphics.h>
#include <conio.h>

int main(void)
{
   /* request autodetection */
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "..\\BGI\\");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
	  cprintf("Graphics error: %s\n", grapherrormsg(errorcode));
	  cprintf("Press any key to halt:");
	  getch();
	  return 1;
   }
   setfillstyle(SOLID_FILL,WHITE);
   floodfill(0,0,WHITE);
   //-----------------------
   setcolor(BLACK);
   char *strheading="Sokoban";
   settextstyle(9, HORIZ_DIR, 0);
   setusercharsize(4, 3, 4, 3);
   outtextxy(15,0,strheading);

   int h=textheight(strheading)+10;
   int w=textwidth(strheading);
   line(0,h,20+w,h);

   //Serifs
   line(15+w,h,20+w,h+5);
   line(20+w,h,25+w,h+5);
   /*
   setcolor(BLACK); //Text
   settextstyle(9, HORIZ_DIR, 0);
   setusercharsize(4, 3, 4, 3);
   outtextxy(14,-1,strheading);

   line(-1,h-1,19+w,h-1);

   //Serifs
   line(14+w,h-1,19+w,h+4);
   line(19+w,h-1,24+w,h+4);
   */
   /* clean up */
   getch();
   closegraph();
   return 0;
}
