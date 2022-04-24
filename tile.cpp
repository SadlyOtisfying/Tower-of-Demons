#include "tile.h"

#include <cstdlib>

using namespace std;

// generate value of tile
void Tile::generate(int level, string type) {
    this->level = level;
    this->type = type;
    if (type == "POTION") {
        value = rand() % 10 + 10;
    } else if (type == "SWORD") {
        value = (rand() % 5 + 3) * level;
    } else if (type == "ARMOR") {
        value = (rand() % 5 + 5) * level;
    } else if (type == "DEMON") {
        hp = (rand() % 5 + 5) * level;
        atk = (rand() % 4 + 1) * level;
        def = (rand() % 5 + 5) * level;
    }
}

void Tile::removeItem() {
    type = "SPACE";
}