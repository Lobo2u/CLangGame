#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define KbUP 0x48
#define kbLEFT 0x4B
#define kbRIGTH 0x4D
#define kbDOWN 0x50

struct Mop
	{
		double dHp;
		double dAtt;
		double dDef;
	};



int main(int argc, char *argv[]){

	int iHeroHp = 100, iHeroAtt = 10, iHeroDef = 4;
	int iMenu = -1;
	char cPosition;
	int iCenterX=7, iCenterY=7, iExit=0, iEvent=-1;
	
	//file combination with move.c
	//function
	//function collection 
	//in 1 file 
	
	//structure
	struct Mop strMop1, strMop2, strMop3, strMopFight;
	//Mop 1
	strMop1.dHp = 100;
	strMop1.dAtt = 8;
	strMop1.dDef = 3;
	//Mop 2
	strMop2.dHp = 80;
	strMop2.dAtt = 8;
	strMop2.dDef = 3;
	//Mop 3
	strMop3.dHp = 50;
	strMop3.dAtt = 8;
	strMop3.dDef = 3;

	//console size fix
	system("mode con:cols=90 lines=50");

	printf("\t\t\t\t\t\t\tLobo's Adventure :)");
	// functin  divide the screen
	DrawScreenLine();
	
	//Main
	gotoXY(30, 15);
	printf("Lobo's Adventure\n");
	
	for(; ;)	//while(1)
	{
		//Menu
		gotoXY(50, 31);
		printf("## 메인 메뉴 ##");
		gotoXY(50, 32);
		printf("새 게임(0)");
		gotoXY(50, 33);
		printf("불러오기(1)");
		gotoXY(50, 34);
		printf("나가기(기타)");
		
		scanf("%d",  &iMenu);
			
		if(iMenu == 0)	//New Game
		{	
			//Main
			ClearMainScreen();
			gotoXY(30, 15);
			printf("새 게임");
			
			for(; ;)	//while(1)
			{
				//game menu
				ClearMenuBox();
				gotoXY(50, 31);
				printf("## 게임 메뉴 ##");
				gotoXY(50, 32);
				printf("던전 입장(0)");
				gotoXY(50, 33);
				printf("Village 입장(0)");
				gotoXY(50, 34);
				printf("나가기(기타)");

				scanf("%d", &iMenu);
				
				if(iMenu == 0)	//enter dungeon
				{
					//Main
					ClearMainScreen();
					//gotoXY(30, 15);
					//printf("던전 입장\n");
					DrawMap();
					
					for(;  ;) //while(1)
					{
					//던전 메뉴
						ClearMenuBox();
						gotoXY(50, 31);
						printf("## 던전 메뉴 ##");
						gotoXY(50, 32);
						printf("이동(방향키 사용)");
						gotoXY(50, 33);
						printf("나가기(1)");
						
						
						//Starting Point
						gotoXY(iCenterX, iCenterY);
						printf("*");
						
						while(1)
						{
							if(kbhit())
							{
								//character prev loc delete	
								gotoXY(iCenterX, iCenterY);
								printf(" ");
						
								cPosition = linux_getch();
	
								switch(cPosition)
								{
								case 'w': //up
								case KbUP:
										iCenterY--;
										break;		
								case 's':	//down
								case kbDOWN:
									iCenterY++;
									break;
								case 'a': //left
								case kbLEFT:
									iCenterX--;
									break;
								case 'd': //right
								case kbRIGTH:
									iCenterX++;
									break;
								case '1': //exit
									iExit = 1;
									break;
								}
	
								//map size setting
								if(iCenterX <= 6)
								{
									iCenterX++;
								}
								if(iCenterX >= 49)
								{
									iCenterX--;
								}
								if(iCenterY <= 6)
								{
									iCenterY++;
								}
								if(iCenterY >= 25)
								{
									iCenterY--;
								}
								
								gotoXY(iCenterX, iCenterY);
								printf("*");
								}
						
								//compare current loc and map event occur 
								iEvent = GetEventFromMap(iCenterX, iCenterY);
						
								if(iEvent == 0)
								{
									iMenu = 0;
									iCenterX++;
									break;
								}
								
								if(iExit == 1)	//Exit
								{
									iMenu = 1;
									break;
								}
							}

							if(iMenu == 0)	//	이동
							{
								printf("이동\n");
							
								int iRandomMove=0;
								//return value is 0~9 Rand function						
								iRandomMove = RPGRandom(10);
						
								if(iRandomMove < 1)	//20%
							//////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Event
							{
								//Text Box
								ClearTextBox();
								gotoXY(2, 32);
								printf("금화를 10원 획득하였습니다.");
							}
							else if(iRandomMove > 6)
						/////////////////////////////////////////////////////////////////////////////////////////////////////////
						//No Event
						{
						//Text Box
							ClearTextBox();
							gotoXY(2, 32);
							printf("아무일도 일어나지 않았습니다.");
						}
						else
						{
							//return value is 0~2 Rand function						
							iRandomMove = RPGRandom(3);
							
							if(iRandomMove == 0)
							{
							//Main
								ClearMap();
								gotoXY(30, 15);
								printf("mop1 전투시작");
							//Text Box
								ClearTextBox();
								gotoXY(2, 32);
								printf("mop1을 만났습니다.");
								strMopFight = strMop1;
							}
							else if(iRandomMove == 1)
							{
								//Main
								ClearMap();
								gotoXY(30, 15);
								printf("mop2 전투시작");

								//Text Box
								ClearTextBox();
								gotoXY(2, 32);
								printf("mop2을 만났습니다.");
								strMopFight = strMop2;
							}
							else
							{
								//Main
								ClearMap();
								gotoXY(30, 15);
								printf("mop3 전투시작");
							
								//Text Box
								ClearTextBox();
								gotoXY(2, 32);
								printf("mop3을 만났습니다.");
								strMopFight = strMop3;
							}
							
							
							//////////////////////////////////////////////////////////////////////////////////////////////////////////
							//Battle
							for(; ;)	//while(1)
							{
							//던전 메뉴
							ClearMenuBox();
							gotoXY(50, 31);
							printf("## 전투 메뉴 ##");
							gotoXY(50, 32);
							printf("공격(0)");
							gotoXY(50, 33);
							printf("방어(1)");
							gotoXY(50, 34);
							printf("후퇴(기타)");
							scanf("%d", &iMenu);
							
							//definition of attack, defense, withdraw
							//attack = character attack 1, monster attack 1
							//defense = character defense(defense 2 increase), moster attack
							//withdraw = moster attack(10% of attack) 1
							
							//damage function definition
							//defense - attack


							if(iMenu == 0) //	전투
							{
								//printf("공격\n");
									
									//Text Box
								ClearTextBox();
								gotoXY(2, 32);
									//character attack 1
								printf("주인공이 몬스터를 공격합니다.");
								strMopFight.dHp = AttackAtoB(iHeroAtt, strMopFight.dDef, strMopFight.dHp, 32);
								
								//Text box
								gotoXY(2, 35);
								//monster attack 1
								printf("몬스터가 반격 합니다.");
								iHeroHp = AttackAtoB(strMopFight.dAtt, iHeroDef, iHeroHp, 35 );
							}
							else if(iMenu == 1) //defense
							{
								//printf("방어");
									
										//Text Box
								ClearTextBox();
								gotoXY(2, 32);
									//character defense(+방어력 +2)
								printf("주인공이 방어 자세를 취합니다.");
								gotoXY(2, 34);
								printf("몬스터가 공격합니다.");
								iHeroHp = AttackAtoB(strMopFight.dAtt, iHeroDef+2, iHeroHp,34);
									}
							else			 //후퇴
							{
								//Text Box
								ClearTextBox();
								gotoXY(2, 32);
								//withdraw = moster counterattack(attack - 2) 1
								printf("주인공이 후퇴를 시도합니다.");
								
								gotoXY(2, 34);
								printf("몬스터가 공격합니다.");
								iHeroHp = AttackAtoB(strMopFight.dAtt - 2, iHeroDef, iHeroHp,34);
								//Main menu
								ClearMainScreen();
								//gotoXY(30, 15);
								//printf("던전");
								DrawMap();
								
								//Text Box
								ClearTextBox();
								gotoXY(2, 32);							
								printf("던전으로 이동");
								break;			//break는 자신의 반복문을 종료
							}
							
							if(strMopFight.dHp <= 0)
							{
								//Main menu
								ClearMainScreen();
								//gotoXY(30, 15);
								//printf("던전");
								DrawMap();
								
								//Text Box
								ClearTextBox();
								gotoXY(2, 32);
								printf("전투에 승리하였습니다.");
								break;
							}
						
						/////////////////////////////////////////////////////////////////////////////////////////
						}
					}
					}
					else
					{
						//game menu
						ClearMap();
						//ClearMainScreen();
						gotoXY(30, 15);
						printf("게임 메뉴");
						
						//Text Box
						ClearTextBox();
						gotoXY(2, 32);
						printf("게임 메뉴로 이동");
						break;
					}	
				}
			}
			else	//exit
			{
				//Main menu
				ClearMainScreen();
				gotoXY(30, 15);
				printf("메인 메뉴");
				
				//Text Box
				ClearTextBox();
				gotoXY(2, 32);
				printf("메인 메뉴로 이동");
				break;
				}
			}
		}
		else //exit
		{
				//Main menu
				ClearMainScreen();
				gotoXY(30, 15);
				printf("Bye~ Bye~");
				
				//Text Box
				ClearTextBox();
				gotoXY(2, 32);
				printf("게임을 종료합니다.");
				break;
		}
	}

		return 0;
}


