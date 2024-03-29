#include "player.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

// load the player from playerdata.txt
void Player::load() {
    ifstream fin;
    fin.open("playerdata.txt");
    if (fin.fail()) {
        fin.close();
        reset();
    } else {
        fin >> diff >> level >> hp >> atk >> def >> lastSaved;
        x = 0;
        y = 0;
        cout << "Player has been loaded from " << ctime(&lastSaved);
        fin.close();
    }
}

// save the player to playerdata.txt
void Player::save() {
    ofstream fout;
    fout.open("playerdata.txt");
    if (fout.fail()) {
        cout << "Error in saving player :(" << endl;
        exit(1);
    }
    fout << diff << endl;
    fout << level << endl;
    fout << hp << endl;
    fout << atk << endl;
    fout << def << endl;
    time(&lastSaved);
    fout << lastSaved <<endl;
    fout.close();
    cout << "Player last saved at " << ctime(&lastSaved);
}

// reset player status
void Player::reset() {
    diff = -1;
    x = 0;
    y = 0;
    level = 0;
    hp = 100;
    atk = 2;
    def = 2;
    cout << "A new player has been created." << endl;
    save();
}