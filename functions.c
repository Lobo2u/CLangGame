#include "functions.h"

static const char DUNGEON_TEMPLATE[MAP_H][MAP_W + 1] = {
	"######################",
	"#................$...#",
	"#..M.................#",
	"#........Q...........#",
	"#..............+.....#",
	"#.....M..............#",
	"#....................#",
	"#..................E.#",
	"######################"
};

static const Monster MONSTERS[] = {
	{
		"Slime",
		"   (o o)\n"
		"   /___\\",
		18, 8, 1
	},
	{
		"Wolf",
		"   /\\_/\\\n"
		"  ( o.o )\n"
		"   > ^ <",
		24, 11, 2
	},
	{
		"Orc",
		"    .--.\n"
		"   |o  o|\n"
		"    \\__/",
		30, 14, 3
	}
};

void clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

void print_banner(const char *subtitle)
{
	printf("========================================\n");
	printf("         LOBO'S ADVENTURE\n");
	if (subtitle && subtitle[0] != '\0') {
		printf("         %s\n", subtitle);
	}
	printf("========================================\n");
}

void print_status(const Player *p)
{
	printf("HP %d/%d   ATK %d   DEF %d   Gold %d   Potions %d\n",
	       p->hp, p->maxHp, p->att, p->def, p->gold, p->potions);
	print_quest_status(p);
}

void pause_continue(void)
{
	printf("\n(Enter to continue) ");
	if (!isatty(STDIN_FILENO)) {
		printf("\n");
		fflush(stdout);
		return;
	}
	(void)read_char();
}

void print_quest_status(const Player *p)
{
	printf("Quest: ");
	switch (p->quest) {
	case QUEST_ACTIVE:
		printf("Find the Lost Amulet in the dungeon.\n");
		break;
	case QUEST_FOUND:
		printf("Return the Lost Amulet to the elder.\n");
		break;
	case QUEST_DONE:
		printf("Lost Amulet returned. The village is grateful.\n");
		break;
	default:
		printf("None yet. Talk to the village elder.\n");
		break;
	}
}

int read_int(void)
{
	char buf[64];

	fflush(stdout);
	if (fgets(buf, sizeof buf, stdin) == NULL) {
		return -999;
	}
	/* empty line */
	if (buf[0] == '\n') {
		return -1;
	}

	{
		int value = 0;
		if (sscanf(buf, "%d", &value) != 1) {
			return -1;
		}
		return value;
	}
}

char read_char(void)
{
	char buf[64];
	size_t i;

	fflush(stdout);
	if (fgets(buf, sizeof buf, stdin) == NULL) {
		return 'q';
	}
	for (i = 0; buf[i] != '\0'; i++) {
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' &&
		    buf[i] != '\r') {
			return buf[i];
		}
	}
	return 0;
}

int AttackAtoB(int iAttA, int iDefB, int iHpB)
{
	int damage = iAttA - iDefB;

	if (damage < 1) {
		damage = 1;
	}
	return iHpB - damage;
}

int RPGRandom(int iPercent)
{
	if (iPercent <= 0) {
		return 0;
	}
	return rand() % iPercent;
}

void init_player(Player *p)
{
	p->hp = HERO_MAX_HP;
	p->maxHp = HERO_MAX_HP;
	p->att = HERO_ATT;
	p->def = HERO_DEF;
	p->gold = 0;
	p->potions = HERO_START_POTIONS;
	p->x = 1;
	p->y = 1;
	p->quest = QUEST_NONE;
}

void init_dungeon(char dungeon[MAP_H][MAP_W], const Player *p)
{
	int y;
	int x;

	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			dungeon[y][x] = DUNGEON_TEMPLATE[y][x];
		}
	}
	/* Amulet stays gone after it has been found or turned in. */
	if (p->quest == QUEST_FOUND || p->quest == QUEST_DONE) {
		for (y = 0; y < MAP_H; y++) {
			for (x = 0; x < MAP_W; x++) {
				if (dungeon[y][x] == 'Q') {
					dungeon[y][x] = '.';
				}
			}
		}
	}
}

void draw_dungeon(const char dungeon[MAP_H][MAP_W], const Player *p)
{
	int y;
	int x;

	printf("\n");
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			if (x == p->x && y == p->y) {
				putchar('*');
			} else {
				putchar(dungeon[y][x]);
			}
		}
		putchar('\n');
	}
	printf("* you  # wall  M monster  $ gold  + potion  Q amulet  E exit\n");
}

int use_potion(Player *p)
{
	int healed;

	if (p->potions <= 0) {
		printf("You have no heal potions.\n");
		return 0;
	}
	if (p->hp >= p->maxHp) {
		printf("You are already at full health. The potion stays in your pack.\n");
		return 0;
	}

	p->potions--;
	healed = POTION_HEAL;
	p->hp += healed;
	if (p->hp > p->maxHp) {
		healed -= (p->hp - p->maxHp);
		p->hp = p->maxHp;
	}
	printf("You drink a heal potion and recover %d HP. (%d left)\n",
	       healed, p->potions);
	return 1;
}

void faint_to_village(Player *p)
{
	printf("\n*** Your HP dropped to 0! ***\n");
	printf("You collapse. Villagers carry you back to Meadowrest.\n");
	printf("You wake at the inn, fully healed. (Pokemon-style return)\n");
	p->hp = p->maxHp;
	p->x = 1;
	p->y = 1;
}

void talk_elder(Player *p)
{
	printf("\nElder Bran: \"Welcome, traveler.\"\n");

	if (p->quest == QUEST_NONE) {
		printf("Elder Bran: \"A Lost Amulet was stolen into the dungeon.\n");
		printf("             Bring it back and the village will reward you.\"\n");
		p->quest = QUEST_ACTIVE;
		printf("\n[Quest accepted: Find the Lost Amulet]\n");
		return;
	}
	if (p->quest == QUEST_ACTIVE) {
		printf("Elder Bran: \"The amulet still sleeps among those stones.\n");
		printf("             Look for a tile marked Q.\"\n");
		return;
	}
	if (p->quest == QUEST_FOUND) {
		printf("Elder Bran: \"You found it! The well-light returns.\"\n");
		printf("Elder Bran: \"Take 50 gold and a heal potion, with our thanks.\"\n");
		p->gold += 50;
		p->potions += 1;
		p->quest = QUEST_DONE;
		printf("\n[Quest complete: +50 gold, +1 heal potion]\n");
		return;
	}
	printf("Elder Bran: \"Rest when you must. The dungeon is never truly empty.\"\n");
}

Monster pick_monster(void)
{
	return MONSTERS[RPGRandom((int)(sizeof MONSTERS / sizeof MONSTERS[0]))];
}

static int apply_damage_to_hero(Player *p, int monster_att, int bonus_def)
{
	int before = p->hp;
	int after = AttackAtoB(monster_att, p->def + bonus_def, p->hp);
	int dealt = before - after;

	p->hp = after;
	if (p->hp < 0) {
		p->hp = 0;
	}
	return dealt;
}

int combat(Player *p, const Monster *m)
{
	Monster foe = *m;
	int choice;

	clear_screen();
	print_banner("BATTLE");
	printf("%s\n%s\n\n", foe.name, foe.art);

	while (1) {
		printf("You: %d/%d     %s: %d\n", p->hp, p->maxHp, foe.name, foe.hp);
		printf("  0) Attack\n");
		printf("  1) Defend\n");
		printf("  2) Use heal potion\n");
		printf("  3) Flee\n");
		printf("> ");
		choice = read_int();
		if (choice == -999) {
			return COMBAT_FLEE;
		}

		if (choice == 0) {
			int before = foe.hp;
			foe.hp = AttackAtoB(p->att, foe.def, foe.hp);
			printf("You strike the %s for %d damage.\n",
			       foe.name, before - foe.hp);
			if (foe.hp <= 0) {
				int loot = 5 + RPGRandom(11);
				p->gold += loot;
				printf("The %s falls. You find %d gold.\n", foe.name, loot);
				return COMBAT_WIN;
			}
			{
				int dealt = apply_damage_to_hero(p, foe.att, 0);
				printf("The %s hits you for %d damage.\n", foe.name, dealt);
			}
		} else if (choice == 1) {
			int dealt;
			printf("You raise your guard. (+2 DEF this turn)\n");
			dealt = apply_damage_to_hero(p, foe.att, 2);
			printf("The %s hits you for %d damage.\n", foe.name, dealt);
		} else if (choice == 2) {
			use_potion(p);
			{
				int dealt = apply_damage_to_hero(p, foe.att, 0);
				printf("The %s hits you for %d damage.\n", foe.name, dealt);
			}
		} else if (choice == 3) {
			int nick_att = foe.att - 4;
			int dealt;
			if (nick_att < 1) {
				nick_att = 1;
			}
			printf("You try to flee. The %s nicks you on the way out.\n",
			       foe.name);
			dealt = apply_damage_to_hero(p, nick_att, 0);
			printf("You take %d damage.\n", dealt);
			if (p->hp <= 0) {
				faint_to_village(p);
				return COMBAT_DEAD;
			}
			return COMBAT_FLEE;
		} else {
			printf("Choose 0-3.\n");
			continue;
		}

		if (p->hp <= 0) {
			faint_to_village(p);
			return COMBAT_DEAD;
		}
		printf("\n");
	}
}
