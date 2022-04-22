#ifndef TILE_H
#define TILE_H

#include <string>

using namespace std;

struct Tile {
    string type = "";
    void removeItem();
    bool isItem();
    bool isDemon();
    Tile();
    struct item {
        int value;
    };
    struct demon {
        int hp, atk, def;
    };
};

#endif
