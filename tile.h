#ifndef TILE_H
#define TILE_H

#include <string>
#include "player.h"

using namespace std;

struct Tile {
    int level;
    string type = "";
    int value, atk, def;
    double hp;
    bool visible = false;
    void generate(int level, string type);
    bool battle(Player& p);
    void removeItem();
};

#endif
