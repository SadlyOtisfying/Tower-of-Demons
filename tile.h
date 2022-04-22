#ifndef TILE_H
#define TILE_H

#include <string>

using namespace std;

struct Tile {
    string type = "";
    void removeItem();
    Tile(int level, string type);
    struct item {
        int value;
        void generate();
    };
    struct demon {
        int hp, atk, def;
        void generate();
    };
};

#endif
