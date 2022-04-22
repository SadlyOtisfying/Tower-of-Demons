#include "tile.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Tile::Tile(int level, string type) {
    this->level = level;
    this->type = type;
}

string Tile::getType() {
    return type;
}

//generate value of tile
void Tile::generate() {
    srand(time(NULL));
    if (type == "POTION") {
        value = rand() % 10 + 10;
    }
    else if (type == "SWORD") {
        value = (rand() % 5 + 3) * level;
    }
    else if (type == "ARMOR") {
        value = (rand() % 5 + 5) * level;
    }
    else if (type == "DEMON") {
        hp = (rand() % 5 + 5) * level;
        atk = (rand() % 4 + 1) * level;
        def = (rand() % 5 + 5) * level;
    }
}

void Tile::battle() {

}

void Tile::removeItem() {
    type = "SPACE";
}