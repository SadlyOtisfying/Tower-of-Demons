#include "player.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// load the player from playerdata.txt
void Player::loadPlayer() {
    ifstream fin;
    fin.open("playerdata.txt");
    if (fin.fail()) {
        fin.close();
        reset();
    } else {
        fin >> level >> hp >> atk >> def;
        fin.close();
    }
}

// save the player to playerdata.txt
void Player::savePlayer() {
    ofstream fout;
    fout.open("playerdata.txt");
    if (fout.fail()) {
        cout << "Error in saving player :(" << endl;
        exit(1);
    }
    fout << level << endl;
    fout << hp << endl;
    fout << atk << endl;
    fout << def << endl;
    fout.close();
    cout << "Player has been saved." << endl;
}

void Player::reset() {
    x = 0;
    y = 0;
    level = 0;
    hp = 100;
    atk = 2;
    def = 2;
    cout << "A new player has been created." << endl;
    remove("playerdata.txt");
    savePlayer();
}