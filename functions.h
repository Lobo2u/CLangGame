#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAP_H 9
#define MAP_W 22

#define HERO_MAX_HP 40
#define HERO_ATT 10
#define HERO_DEF 3
#define HERO_START_POTIONS 2
#define POTION_HEAL 25

#define QUEST_NONE 0
#define QUEST_ACTIVE 1
#define QUEST_FOUND 2
#define QUEST_DONE 3

#define COMBAT_WIN 0
#define COMBAT_FLEE 1
#define COMBAT_DEAD 2

typedef struct {
	int hp;
	int maxHp;
	int att;
	int def;
	int gold;
	int potions;
	int x;
	int y;
	int quest;
} Player;

typedef struct {
	const char *name;
	const char *art;
	int hp;
	int att;
	int def;
} Monster;

void clear_screen(void);
void print_banner(const char *subtitle);
void print_status(const Player *p);
void print_quest_status(const Player *p);
void pause_continue(void);

int read_int(void);
char read_char(void);

int AttackAtoB(int iAttA, int iDefB, int iHpB);
int RPGRandom(int iPercent);

void init_player(Player *p);
void init_dungeon(char dungeon[MAP_H][MAP_W], const Player *p);
void draw_dungeon(const char dungeon[MAP_H][MAP_W], const Player *p);

int use_potion(Player *p);
void faint_to_village(Player *p);
void talk_elder(Player *p);
Monster pick_monster(void);
int combat(Player *p, const Monster *m);

#endif
