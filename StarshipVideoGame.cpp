#include<stdio.h>
#include<windows.h>
#include<conio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

//starship paint class
class StarShip{
	int x,y;
	
	//all accesible methods
	public:
		StarShip(int _x, int _y):x(_x),y(_y){};
		void paint();
		void erase();
		void move();
		
};

void goToCoords(int x, int y)
{
	//identifier to get the console 
	HANDLE hCon;
	
	//use the identifier output of the console 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//coords in the console
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	//set the cursor of the screen with the coordinates
	SetConsoleCursorPosition(hCon,dwPos);
}

void StarShip::paint() //make reference of the class method with ::
{
	//paint the starship with characters
	goToCoords(x,y); printf("   %c",65);
	goToCoords(x,y+1);printf("  %c%c%c",40,207,41);
	goToCoords(x,y+2);printf(" %c%c %c%c",65,190,190,65);
}

void StarShip::erase()
{
	goToCoords(x,y); printf("      ");
	goToCoords(x,y+1);printf("       ");
	goToCoords(x,y+2);printf("          ");
}

void StarShip::move()
{
	//if a key was pressed
		if(kbhit())
		{
			char key = getch(); //save the key that was pressed
			erase();
			if(key == LEFT && x>3)
				x--;
			if(key == RIGHT && x+10 < 77)
				x++;
			if(key == UP && y > 4)
				y--;
			if(key == DOWN && y+3 < 28)
				y++;
			
			paint();
			
		}
}



void hideCursor()
{
		//identifier to get the console 
	HANDLE hCon;
	
	//use the identifier output of the console 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//set cursor not visible with their functions
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE; 
	
	SetConsoleCursorInfo(hCon,&cci); //pass cci with reference using &
}

void paintLimits()
{
	//paint all the limits of the scenario
	//paint vertical bars
	for(int i=2 ; i<78; i++){
		goToCoords(i,3);printf("%c",205);
		goToCoords(i,28);printf("%c",205);
	}
	//paint horizontal bars
	for(int i=4 ; i<28; i++){
		goToCoords(2,i);printf("%c",186);
		goToCoords(77,i);printf("%c",186);
	}
	//paint the squares
		goToCoords(2,3);printf("%c",201);
		goToCoords(2,28);printf("%c",200);
		goToCoords(77,3);printf("%c",187);
		goToCoords(77,28);printf("%c",188);
}

int main()
{   
	
	hideCursor();
	paintLimits();
	//variable declaration
	bool game_over = false;
	int x = 10, y = 10;
	StarShip starShip(x,y);
	starShip.paint();
	
	
	
	while(!game_over)
	{
		
		starShip.move();
		Sleep(30); // reduce iterations 
	}
	return 0;
}
