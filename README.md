# CLangGame

Team: eunsoo jo, dohyun yoon

Linux console RPG written in C. ASCII only. No extra assets or libraries.

**Status: MVP complete**

## Build

```bash
make
```

Or:

```bash
gcc -Wall -Wextra -std=c99 -o clanggame main.c functions.c
```

Run:

```bash
./clanggame
```

`make clean` removes the binary.

## How to play

Start a new game from the title screen, then play from the village.

### Title
- `0` New Game
- `1` Quit

### Village (Meadowrest)
- `1` Talk to Elder Bran (NPC dialogue + Lost Amulet quest)
- `2` Use a heal potion (+25 HP, will not consume one at full health)
- `3` Enter the dungeon
- `4` Return to the title screen

You begin with 40 HP and 2 heal potions.

### Dungeon
Walk with `w` `a` `s` `d`. Use `p` to drink a heal potion. Use `q` (or step on `E`) to leave.

| Symbol | Meaning |
|--------|---------|
| `*` | You |
| `#` | Wall |
| `M` | Monster (combat) |
| `$` | Gold |
| `+` | Heal potion |
| `Q` | Lost Amulet (quest) |
| `E` | Exit to village |

Empty floor tiles can also trigger a wandering monster or a short quest hint.

### Combat
- `0` Attack
- `1` Defend (+2 DEF that turn)
- `2` Use a heal potion (the monster still strikes)
- `3` Flee (take a smaller hit and step back)

### Death and healing
If HP drops to 0 in combat (or while fleeing), you faint, return to the village automatically, and wake up fully healed — the Pokemon-style safety net from the original plan.

## Quest stub

1. Talk to Elder Bran and accept **Find the Lost Amulet**.
2. Enter the dungeon and step on `Q`.
3. Return to the elder for 50 gold and an extra heal potion.

## Project files

- `main.c` — title / village / dungeon loop
- `functions.c`, `functions.h` — status, map, combat, NPC, items
- `kbhit.h`, `main.h` — leftover from the earlier Windows/Linux port; not required to build
