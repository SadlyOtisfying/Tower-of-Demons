#ifndef TILE_H
#define TILE_H

#include "player.h"
#include <string>

using namespace std;

struct Tile {
    int level;
    string type = "";
    int value, atk, def;
    double hp;
    Tile(int level, string type);
    string getType();
    void generate();
    void battle(Player &p);
    void removeItem();
};

#endif
