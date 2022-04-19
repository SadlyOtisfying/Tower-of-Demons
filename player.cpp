#include "player.h"

#include <fstream>
#include <iostream>

using namespace std;

void Player::loadPlayer() {
    ifstream fin;
    fin.open("playerdata.txt");
    if (fin.fail()) {
        cout << "Error in file opening" << endl;
        exit(1);
    }
    fin >> this->level >> this->hp >> this->atk >> this->def;
    fin.close();
}

void Player::savePlayer() {
    ofstream fout;
    fout.open("playerdata.txt");
    if (fout.fail()) {
        cout << "Error in file opening" << endl;
        exit(1);
    }
    fout << this->level << endl;
    fout << this->hp << endl;
    fout << this->atk << endl;
    fout << this->def << endl;
    fout.close();
}