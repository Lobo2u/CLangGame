#include "functions.h"

int iMap1[20][44]=
	{	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,9,
		9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,9,
		9,5,5,4,5,5,5,4,4,4,5,5,5,5,4,4,4,5,5,5,5,4,4,4,4,4,5,5,5,5,5,5,4,4,5,5,5,4,4,4,4,4,5,9,
		9,5,4,5,4,4,4,5,5,5,4,4,4,4,5,4,5,4,4,4,4,5,4,4,4,5,4,4,4,4,4,4,5,5,4,4,4,5,4,5,5,5,4,9,
		9,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,4,4,4,4,4,5,5,5,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,4,4,4,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
	};
//////////////////////////////////////////////////////////////////////////////////
////////////function A attack B
////////////////////////////////////////////////////////////////////////////////
int AttackAtoB(int iAttA, int iDefB, int iHpB, int iCurrentY) //a attack b and b get the damage
{
	int iDamage=0;
	//calc the Damage.
	iDamage = iDefB - iAttA;
	if(iDamage < 0)
	{
		iHpB = iHpB + iDamage;
		
		//Text Box
		gotoXY(2, iCurrentY+1);
		printf("피해를 %d 입혔습니다.", iDamage);
		gotoXY(2, iCurrentY+2);
		printf("남은 체력  : %d\n", iHpB);
		}
	else
	{
		//Text Box
		gotoXY(2, iCurrentY+1);
		printf("공격에 실패 하셨습니다.");
	}
	return iHpB;//hp after get damage
}

////////////////////////////////////////////////////////////////////////////////////
////////////////Random function(return percent value)
///////////////////////////////////////////////////////////////////////////////////
int RPGRandom(int iPrecent)
{
 	int iRand=0, iRandomResult=0;
	srand(time(NULL));
	iRand = rand();
							
	iRandomResult  = iRand % iPrecent;
	
	return iRandomResult;
}

//////////////////////////////////////////////////////////////////////
// function move to XY
/////////////////////////////////////////////////////////////////////
void gotoXY(int x, int y) 
{
      printf("%c[%d;%df", 0x1B, y, x); 
}


	/*COORD Cursor;
	Cursor.x = x;
	Cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
*/


/////////////////////////////////////////////////////////////////
//function delete menu
///////////////////////////////////////////////////////////////
void ClearMenuBox()
{
	gotoXY(50, 31);
	printf("                                                     ");
	gotoXY(50, 32);
	printf("                                                     ");
	gotoXY(50, 33);
	printf("                                                     ");
	gotoXY(50, 34);
	printf("                                                     ");
}

/////////////////////////////////////////////////////////////
//function delete main
//////////////////////////////////////////////////////////
void ClearMainScreen()
{
	gotoXY(30, 15);
	printf("                                  ");
}

/////////////////////////////////////////////////////////////
//function delete Text
//////////////////////////////////////////////////////////
void ClearTextBox()
{
	gotoXY(2, 32);
	printf("                                                      ");
	gotoXY(2, 33);
	printf("                                                      ");
	gotoXY(2, 34);
	printf("                                                       ");
	gotoXY(2, 35);
	printf("                                                       ");
	gotoXY(2, 36);
	printf("                                                       ");
	gotoXY(2, 37);
	printf("                                                       ");
}

/////////////////////////////////////////////////////////////
//function drawming main screen line
//////////////////////////////////////////////////////////
void DrawScreenLine()
{
	//top line
	gotoXY(0, 1);
	printf("---------------------------------------------------------------------");
	//bottom line
	gotoXY(0, 30);
	printf("--------------------------------------------------------------------");
}

/////////////////////////////////////////////////////////////
//function drawming map on main
//////////////////////////////////////////////////////////
void DrawMap(){
	
	int iIndexX=0, iIndexY=0;
	
	 for(iIndexY=0; iIndexY<20; iIndexY++)
	 {
	 	gotoXY(6, 6+iIndexY);
	 	for(iIndexX=0; iIndexX<44; iIndexX++)
	 	{
	 		if(iMap1[iIndexY][iIndexX] == 9)
	 		{
	 		printf("#");	//border
	 		}
	 		else if(iMap1[iIndexY][iIndexX] == 7)
			{
				printf("+");	//monster
			}
			else if(iMap1[iIndexY][iIndexX] ==3) 
			{
				printf("$"); //coin
			}
			else if(iMap1[iIndexY][iIndexX] ==4) 
			{
				printf("^"); //mountain
			}
	 		else
	 		{
	 			printf(" ");
	 		}		
	 	}
	 	printf("\n");
	 }
}

/////////////////////////////////////////////////////////////
//function removing map from main
//////////////////////////////////////////////////////////
void ClearMap(){

	int iIndexX=0, iIndexY=0;
	
	 for(iIndexY=0; iIndexY<20; iIndexY++)
	 {
	 	gotoXY(6, 6+iIndexY);
	 	for(iIndexX=0; iIndexX<44; iIndexX++)
	 	{
	 		
	 			printf(" ");
	 		}		
	 	}
	 	printf("\n");
	 }


/////////////////////////////////////////////////////////////
//function Compare current loc and Event loc
//////////////////////////////////////////////////////////
int GetEventFromMap(int iCurrentX, int iCurrentY)
{
	int iEventOk=-1;

	 		if(iMap1[iCurrentY][iCurrentX] == 7)
			{
				iEventOk = 0;	//monster
			}
			else if(iMap1[iCurrentY][iCurrentX] ==3) 
			{
				iEventOk = 0;//coin
			}
	 
	 return iEventOk;
}
////////////////////////////////////////////////////////////////
//when you type the keyboard....
///////////////////////////////////////////////////////////////function ‘main’:



int kbhit(void)

{

	struct termios oldt, newt;

	int ch;


	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;


	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);


	ch = getchar();


	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);


	return ch;

}

//////////////////////////////////////////////////////////////////
//getch
////////////////////////////////////////////////////////////////
int linux_getch(void)
{


    int ch;


    struct termios buf, save;


    tcgetattr(0, &save);


    buf = save;


    buf.c_lflag &= ~(ICANON | ECHO);


    buf.c_cc[VMIN] = 1;


    buf.c_cc[VTIME] = 0;


    tcsetattr(0, TCSAFLUSH, &buf);


    ch = getchar();


    tcsetattr(0, TCSAFLUSH, &save);


    return ch;


    //left D , Right C, UP A, DOWN B


}


