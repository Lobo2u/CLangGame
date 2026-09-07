#include "functions.h"

enum {
	ST_TITLE = 0,
	ST_VILLAGE,
	ST_DUNGEON,
	ST_QUIT
};

static int run_title(void);
static int run_village(Player *p);
static int run_dungeon(Player *p);
static int handle_dungeon_tile(Player *p, char dungeon[MAP_H][MAP_W],
			       int old_x, int old_y);

int main(void)
{
	Player hero;
	int state = ST_TITLE;

	srand((unsigned int)time(NULL));
	init_player(&hero);

	while (state != ST_QUIT) {
		if (state == ST_TITLE) {
			state = run_title();
			if (state == ST_VILLAGE) {
				init_player(&hero);
			}
		} else if (state == ST_VILLAGE) {
			state = run_village(&hero);
		} else if (state == ST_DUNGEON) {
			state = run_dungeon(&hero);
		} else {
			state = ST_QUIT;
		}
	}

	clear_screen();
	print_banner("Goodbye");
	printf("Bye~ Bye~\nThanks for playing Lobo's Adventure.\n");
	return 0;
}

static int run_title(void)
{
	int choice;

	clear_screen();
	print_banner("Linux C RPG");
	printf("\n");
	printf("  A small village. A hungry dungeon.\n");
	printf("  Heal, talk, fight, and come home.\n\n");
	printf("## Main Menu ##\n");
	printf("  0) New Game\n");
	printf("  1) Quit\n");
	printf("> ");

	choice = read_int();
	if (choice == 0) {
		return ST_VILLAGE;
	}
	return ST_QUIT;
}

static int run_village(Player *p)
{
	int choice;

	clear_screen();
	print_banner("Village of Meadowrest");
	print_status(p);
	printf("\n");
	printf("  Cottages sit around a stone well. Elder Bran waits nearby.\n");
	printf("  South of town, the dungeon mouth breathes cold air.\n\n");
	printf("## Village Menu ##\n");
	printf("  1) Talk to the village elder (NPC)\n");
	printf("  2) Use a heal potion\n");
	printf("  3) Enter the dungeon\n");
	printf("  4) Quit to title\n");
	printf("> ");

	choice = read_int();
	if (choice == -999) {
		return ST_QUIT;
	}
	if (choice == 1) {
		talk_elder(p);
		pause_continue();
		return ST_VILLAGE;
	}
	if (choice == 2) {
		use_potion(p);
		pause_continue();
		return ST_VILLAGE;
	}
	if (choice == 3) {
		printf("You take the south path into the dungeon...\n");
		return ST_DUNGEON;
	}
	if (choice == 4) {
		return ST_TITLE;
	}

	printf("Choose 1-4.\n");
	return ST_VILLAGE;
}

static int run_dungeon(Player *p)
{
	char dungeon[MAP_H][MAP_W];
	char key;
	int old_x;
	int old_y;
	int nx;
	int ny;

	init_dungeon(dungeon, p);
	p->x = 1;
	p->y = 1;

	while (1) {
		clear_screen();
		print_banner("Dungeon");
		print_status(p);
		draw_dungeon(dungeon, p);
		printf("\nMove (w/a/s/d), potion (p), leave (q)\n> ");

		key = read_char();
		if (key >= 'A' && key <= 'Z') {
			key = (char)(key - 'A' + 'a');
		}

		if (key == 'q') {
			printf("You leave the dungeon and return to the village.\n");
			return ST_VILLAGE;
		}
		if (key == 'p') {
			use_potion(p);
			pause_continue();
			continue;
		}

		old_x = p->x;
		old_y = p->y;
		nx = p->x;
		ny = p->y;
		if (key == 'w') {
			ny--;
		} else if (key == 's') {
			ny++;
		} else if (key == 'a') {
			nx--;
		} else if (key == 'd') {
			nx++;
		} else {
			printf("Use w/a/s/d to walk, p for a potion, q to leave.\n");
			pause_continue();
			continue;
		}

		if (nx < 0 || nx >= MAP_W || ny < 0 || ny >= MAP_H ||
		    dungeon[ny][nx] == '#') {
			printf("A stone wall blocks the way.\n");
			pause_continue();
			continue;
		}

		p->x = nx;
		p->y = ny;
		if (handle_dungeon_tile(p, dungeon, old_x, old_y) != 0) {
			return ST_VILLAGE;
		}
	}
}

static int handle_dungeon_tile(Player *p, char dungeon[MAP_H][MAP_W],
			       int old_x, int old_y)
{
	char tile = dungeon[p->y][p->x];

	if (tile == 'E') {
		printf("Daylight. You step back into the village path.\n");
		pause_continue();
		return 1;
	}

	if (tile == '$') {
		p->gold += 10;
		dungeon[p->y][p->x] = '.';
		printf("You pick up 10 gold. (Event)\n");
		pause_continue();
		return 0;
	}

	if (tile == '+') {
		p->potions += 1;
		dungeon[p->y][p->x] = '.';
		printf("You find a heal potion on a mossy shelf.\n");
		pause_continue();
		return 0;
	}

	if (tile == 'Q') {
		dungeon[p->y][p->x] = '.';
		if (p->quest == QUEST_ACTIVE) {
			p->quest = QUEST_FOUND;
			printf("You uncover the Lost Amulet beneath loose stone.\n");
			printf("[Quest update: return it to Elder Bran]\n");
		} else if (p->quest == QUEST_NONE) {
			p->quest = QUEST_FOUND;
			printf("You find an old amulet. Someone in the village may want it.\n");
		} else {
			printf("An empty alcove. The amulet is already yours.\n");
		}
		pause_continue();
		return 0;
	}

	if (tile == 'M') {
		Monster foe = pick_monster();
		int result;

		printf("A %s blocks the corridor!\n", foe.name);
		result = combat(p, &foe);
		if (result == COMBAT_DEAD) {
			return 1;
		}
		if (result == COMBAT_WIN) {
			dungeon[p->y][p->x] = '.';
		} else {
			p->x = old_x;
			p->y = old_y;
			printf("You stumble back to your last step.\n");
		}
		pause_continue();
		return 0;
	}

	/* Interactive sessions only: wandering fight or a quest hint. */
	if (tile == '.' && isatty(STDIN_FILENO)) {
		int roll = RPGRandom(10);
		if (roll == 0) {
			Monster foe = pick_monster();
			int result;

			printf("Footsteps. A wandering %s attacks!\n", foe.name);
			result = combat(p, &foe);
			if (result == COMBAT_DEAD) {
				return 1;
			}
			pause_continue();
		} else if (roll == 1 && p->quest == QUEST_ACTIVE) {
			printf("Carvings on the wall show an amulet over a well.\n");
			printf("(Quest hint: keep exploring for the Q tile.)\n");
			pause_continue();
		}
	}

	return 0;
}
