#ifndef TILE_H
#define TILE_H

#include <string>

using namespace std;

struct Tile {
    int level;
    string type;
    int value, atk, def;
    double hp;
    bool visible = true;
    void generate(int level, string type);
    void clear();
};

#endif
