#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#include"C:\sokoban\map.cpp"

char *num3dig(int a)
{
	char *str;
	if(a<10)
	{
		str[0]=str[1]='0';
		str+=2;
		itoa(a,str,10);
		str-=2;
		return str;
	}
	if(a<100)
	{
		str[0]='0';
		str++;
		itoa(a,str,10);
		str--;
		return str;
	}
	itoa(a,str,10);
	return str;
}
void main()
{
	clrscr();
	char strin[60]="G:\\C__PRO~1\\SOKOBA~1\\RESOUR~1\\LEVELS\\level";
	char strout[60]="C:\\sokoban\\levels\\level";
	char temp[60]="";
	ifstream ifil;
	int x=0,y=0;
	int r=1,c=1;
	char cell;

	for(int i=1;i<=155;++i) //155 levels
	{
		cout<<"Converting level "<<i<<" of 155...";
		x=y=0;
		strcpy(temp,strin);
		strcat(temp,num3dig(i));
		strcat(temp,".txt");
		ifil.open(temp,ios::in);

		Map out;
		out.num_rows(30);
		out.num_cols(40);

		while(!ifil.eof())
		{
			ifil.get(cell);
			switch(cell)
			{
				case ' ':
					out.set_cell(x,y,c_empty);
					break;
				case '#':
					out.set_cell(x,y,c_wall);
					break;
				case '$':
					out.set_cell(x,y,c_box);
					break;
				case '.':
					out.set_cell(x,y,c_target);
					break;
				case '@':
					out.set_cell(x,y,c_player);
					out.player_x(x);
					out.player_y(y);
					break;
				case '+':
					out.set_cell(x,y,c_player|c_target);
					out.player_x(x);
					out.player_y(y);
					break;
				case '*':
					out.set_cell(x,y,c_box|c_target);
					break;
				case '\n':
					if (x>c) c=x;
					++y;
					x=0;
					break;
			}
			if (cell!='\r'&&cell!='\n') ++x;
		}
		r=y;
		out.num_cols(c);
		out.num_rows(r);
		ifil.close();

		strcpy(temp,strout);
		char *stri;
		itoa(i,stri,10);
		strcat(temp,stri);
		strcat(temp,".dat");
		if(out.save_to_file(temp))
			cout<<"Failed.\n";
		else
			cout<<"Successful\n";
	}
	getch();
}