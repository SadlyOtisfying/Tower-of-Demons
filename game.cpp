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
    map.clear();
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
    cout << "A new map has been generated." << endl;
}

void makeVisible(Player& p, vector<vector<vector<Tile>>>& map) {
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (p.x + j >= 0 && p.x + j < 6 && p.y + i >= 0 && p.y + i < 6)
                map[p.level][p.y + i][p.x + j].visible = true;
}

void display(Player& p, vector<vector<vector<Tile>>>& map) {
    cout << endl;
    int levels = (p.diff + 1) * 2;
    cout << "Level " << p.level + 1 << "/" << levels << "; ";
    cout << "HP " << p.hp << "; ";
    cout << "ATK " << p.atk << "; ";
    cout << "DEF " << p.def << endl;
    makeVisible(p, map);
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

void detectItem(Player& p, vector<vector<vector<Tile>>>& map) {
    Tile& t = map[p.level][p.y][p.x];
    if (t.type == "POTION") {
        cout << endl;
        cout << "You found a potion (+" << t.value << " HP)!" << endl;
        int oldhp = p.hp;
        p.hp = min(p.hp + t.value, 100.00);
        cout << "Added " << p.hp - oldhp << " HP. Your HP is now " << p.hp << "." << endl;
        t.clear();
    } else if (t.type == "SWORD") {
        cout << endl;
        cout << "You found a sword (ATK " << t.value << ")!" << endl;
        if (prompt("Do you want to equip the sword? (0 - No; 1 - Yes): ", 2)) {
            p.atk = t.value;
            cout << "Sword equipped. ";
        } else
            cout << "Sword not equipped. ";
        cout << "Your ATK is now " << p.atk << "." << endl;
        t.clear();
    } else if (t.type == "ARMOR") {
        cout << endl;
        cout << "You found an armor (DEF " << t.value << ")!" << endl;
        if (prompt("Do you want to equip the armor? (0 - No; 1 - Yes): ", 2)) {
            p.def = t.value;
            cout << "Armor equipped. ";
        } else
            cout << "Armor not equipped. ";
        cout << "Your DEF is now " << p.def << "." << endl;
        t.clear();
    }
}

void detectDemon(Player& p, vector<vector<vector<Tile>>>& map) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (p.x + j >= 0 && p.x + j < 6 && p.y + i >= 0 && p.y + i < 6) {
                Tile& t = map[p.level][p.y + i][p.x + j];
                if (t.type == "DEMON") {
                    cout << endl;
                    cout << "You encountered a demon! Entering battle..." << endl;
                    cout << "You: HP " << p.hp << "; ATK " << p.atk << "; DEF " << p.def << endl;
                    cout << "Demon: HP " << t.hp << "; ATK " << t.atk << "; DEF " << t.def << endl;
                    while (p.hp > 0 && t.hp > 0) {
                        t.hp -= p.atk * (1 - t.def * 0.01);
                        cout << "You hit the demon for " << p.atk << " damage, it took " << p.atk * (1 - t.def * 0.01) << " damage, it has " << t.hp << " HP left." << endl;
                        if (t.hp <= 0)
                            break;
                        p.hp -= t.atk * (1 - p.def * 0.01);
                        cout << "The demon hit you for " << t.atk << " damage, you took " << t.atk * (1 - p.def * 0.01) << " damage, you have " << p.hp << " HP left." << endl;
                    }
                    if (t.hp <= 0) {
                        cout << "You have slained the demon!" << endl;
                        t.clear();
                    } else {
                        cout << "YOU DIED. RIP." << endl << endl;
                        p.load();
                        int levels = (p.diff + 1) * 2;
                        generateMap(map, levels);
                        return;
                    }
                }
            }
        }
    }
}

bool start() {
    // make player
    Player p;
    p.load();

    // set difficulty and generate map
    if (p.diff == -1) {
        p.diff = prompt("Please select difficulty (0 - easy; 1 - normal; 2 - hard): ", 3);
        p.save();
    }
    int levels = (p.diff + 1) * 2;
    vector<vector<vector<Tile>>> map;
    generateMap(map, levels);

    // introduction
    cout << "Your love, Princess Lily was captured by some demons and locked in the top of a tower. Now, save her. Good luck." << endl;
    display(p, map);

    // game loop
    while (true) {
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
        } else if (move == "reload") {
            if (prompt("Are you sure to reload? You will be reloaded to your last save. (0 - No; 1 - Yes): ", 2)) {
                p.load();
                generateMap(map, levels);
            }
        } else if (move == "exit") {
            if (prompt("Are you sure to exit? (0 - No; 1 - Yes): ", 2))
                exit(0);
        } else {
            cout << "Invalid move. Type \"help\" to view list of moves and legend." << endl;
        }
        detectItem(p, map);
        detectDemon(p, map);
        if (p.x == 6 - 1 && p.y == 6 - 1) {
            if (p.level == levels - 1)
                break;
            p.level++;
            p.x = 0;
            p.y = 0;
            cout << "You have advanced to level " << p.level + 1 << " of the tower!" << endl;
            p.save();
        }
        display(p, map);
    }

    // ending
    cout << endl;
    cout << "You found Princess Lily tied to a chair. You immediately rescued her." << endl;
    cout << "\"Thanks!\" she said." << endl;
    cout << "THE END." << endl;
    cout << "Credits: Titus Ng, Michael Kong" << endl << endl;

    if (prompt("Restart? (0 - No; 1 - Yes): ", 2)) {
        p.reset();
        cout << endl;
        return true;
    } else
        return false;
}

int main() {
    init();
    while (start());
    return 0;
}
