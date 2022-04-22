#include "tile.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// generate value of tile
void Tile::generate(int level, string type) {
    this->level = level;
    this->type = type;
    srand(time(NULL));
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

// battle the player and the demon. return true if player survives; false if player dies
bool Tile::battle(Player& p) {
    while (p.hp > 0 && hp > 0) {
        hp -= p.atk * (1 - def * 0.01);
        cout << "You hit the demon for " << p.atk << " damage, it took " << p.atk * (1 - def * 0.01) << "damage, it has " << hp << "left." << endl;
        if (hp <= 0)
            break;
        p.hp -= atk * (1 - p.def * 0.01);
        cout << "The demon hit you for " << atk << " damage, you took " << atk * (1 - p.def * 0.01) << "damage, you have " << p.hp << "left." << endl;
    }
    if (hp <= 0) {
        cout << "You have slained the demon!" << endl;
        return true;
    } else {
        cout << "YOU DIED. RIP." << endl;
        return false;
    }
}

void Tile::removeItem() {
    type = "SPACE";
}