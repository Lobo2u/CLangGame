#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//#include "main.h"
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
//#include <cursor.h>
//#include "kbhit.h"
//#include <termios.h>
#include <sys/select.h>
#include <termios.h>

int AttackAtoB(int iAttA, int iDefB, int iHpB, int iCurrentY);
int RPGRandom(int iPrecent);

void gotoXY(int x, int y);
void ClearMenuBox();
void ClearMainScreen();
void ClearTextBox();
void DrawScreenLine();
void DrawMap();
void ClearMap();
int GetEventFromMap(int iCenterX,int iCenterY);
int kbhit(void);
int linux_getch(void);

#endif
