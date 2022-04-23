#include "player.h"
#include "tile.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void init() {
    cout << "Welcome to Tower of Demons!" << endl;
    cout << fixed << setprecision(2);
    srand(time(NULL));
}

// prompt the user for an integer with limited options
int prompt(string output, int options) {
    int ans;
    cout << output;
    string input;
    cin >> input;
    try {
        ans = stoi(input);
        if (ans < 0 || ans >= options)
            throw 1;
    } catch (...) {
        cout << "... This is an invalid input. Are you challenging me? Bad idea ;) The last option has been chosen for you." << endl;
        ans = options - 1;
    }
    return ans;
}

void generateMap(vector<vector<vector<Tile>>>& map, int levels) {
    for (int level = 0; level < levels; level++) {
        vector<vector<Tile>> temp;
        // set all tiles to space
        for (int i = 0; i < 6; i++) {
            vector<Tile> temprow;
            for (int j = 0; j < 6; j++) {
                Tile temptile;
                temptile.generate(level, "SPACE");
                temprow.push_back(temptile);
            }
            temp.push_back(temprow);
        }

        // randomly pick 12 tiles out of 36 tiles of a level
        int random[36];
        for (int j = 0; j < 36; j++)
            random[j] = j;
        random_shuffle(random, random + 36);

        int index = 0;
        // generate potions
        for (int i = 0; i < 3; i++) {
            temp[random[index] / 6][random[index] % 6].generate(level, "POTION");
            index++;
        }
        // generate swords
        for (int i = 0; i < 3; i++) {
            temp[random[index] / 6][random[index] % 6].generate(level, "SWORD");
            index++;
        }
        // generate armors
        for (int i = 0; i < 3; i++) {
            temp[random[index] / 6][random[index] % 6].generate(level, "ARMOR");
            index++;
        }
        // generate demons
        for (int i = 0; i < 3; i++) {
            temp[random[index] / 6][random[index] % 6].generate(level, "DEMON");
            index++;
        }

        map.push_back(temp);
    }
}

void display(Player& p, vector<vector<vector<Tile>>>& map) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (p.x == j && p.y == i)
                cout << "X ";
            else if (map[p.level][i][j].visible) {
                if (map[p.level][i][j].type == "SPACE")
                    cout << ". ";
                else if (map[p.level][i][j].type == "POTION")
                    cout << "P ";
                else if (map[p.level][i][j].type == "SWORD")
                    cout << "S ";
                else if (map[p.level][i][j].type == "ARMOR")
                    cout << "A ";
                else if (map[p.level][i][j].type == "DEMON")
                    cout << "D ";
            } else
                cout << "? ";
        }
        cout << endl;
    }
}

void die() {}

// battle the player and the demon, trigger corresponding function based on result
void battle(Player& p, Tile& t) {
    while (p.hp > 0 && t.hp > 0) {
        t.hp -= p.atk * (1 - t.def * 0.01);
        cout << "You hit the demon for " << p.atk << " damage, it took " << p.atk * (1 - t.def * 0.01) << "damage, it has " << t.hp << "left." << endl;
        if (t.hp <= 0)
            break;
        p.hp -= t.atk * (1 - p.def * 0.01);
        cout << "The demon hit you for " << t.atk << " damage, you took " << t.atk * (1 - p.def * 0.01) << "damage, you have " << p.hp << "left." << endl;
    }
    if (t.hp <= 0) {
        cout << "You have slained the demon!" << endl;
        t.removeItem();
    } else {
        cout << "YOU DIED. RIP." << endl;
        die();
    }
}

void detectItem(Player& p, vector<vector<vector<Tile>>>& map) {}

void detectDemon(Player& p, vector<vector<vector<Tile>>>& map) {}

bool start() {
    // make player
    Player p;
    p.loadPlayer();

    // set difficulty and generate map
    if (p.diff == -1) {
        p.diff = prompt("Please choose the difficulty (0 - easy; 1 - normal; 2 - hard): ", 3);
        p.savePlayer();
    }
    int levels = (p.diff + 1) * 2;
    vector<vector<vector<Tile>>> map;
    generateMap(map, levels);
    cout << "Your love, Princess Lily was captured by some demons and locked in the top of a tower. Now, save her. Good luck." << endl;
    display(p, map);

    // game loop
    while (p.level < levels) {
        cout << "Your move: ";
        string move;
        cin >> move;
        for (char& c : move)
            c = tolower(c);
        if (move == "help") {
        } else if (move == "up" || move == "w") {
            p.y--;
            if (p.y < 0) {
                p.y = 0;
                cout << "You cannot move up." << endl;
            } else
                cout << "You moved up." << endl;
        } else if (move == "left" || move == "a") {
            p.x--;
            if (p.x < 0) {
                p.x = 0;
                cout << "You cannot move left." << endl;
            } else
                cout << "You moved left." << endl;
        } else if (move == "down" || move == "s") {
            p.y++;
            if (p.y > 6 - 1) {
                p.y = 6 - 1;
                cout << "You cannot move down." << endl;
            } else
                cout << "You moved down." << endl;
        } else if (move == "right" || move == "d") {
            p.x++;
            if (p.x > 6 - 1) {
                p.x = 6 - 1;
                cout << "You cannot move right." << endl;
            } else
                cout << "You moved right." << endl;
        } else if (move == "reset") {
        } else if (move == "exit") {
        }
        display(p, map);
        detectItem(p, map);
        detectDemon(p, map);
        if (p.x == 6 - 1 && p.y == 6 - 1) {
            p.level++;
            p.savePlayer();
            cout << "You have advanced to level " << p.level << " of the tower!" << endl;
        }
    }

    // ending
    cout << "You found Princess Lily tied to a chair. You immediately rescued her." << endl;
    cout << "\"Thanks!\" she said." << endl;
    cout << "THE END." << endl;
    cout << "Credits: Titus Ng, Michael Kong" << endl << endl;

    if (prompt("Restart? (0 - No; 1- Yes): ", 2)) {
        p.reset();
        return true;
    } else
        return false;
}

int main() {
    init();
    while (start())
        ;
    return 0;
}
