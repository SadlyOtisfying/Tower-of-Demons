#include "player.h"

#include <fstream>
#include <iostream>

using namespace std;

//load the player from playerdata.txt
void Player::loadPlayer() {
    ifstream fin;
    fin.open("playerdata.txt");
    if (fin.fail()) {
        cout << "Error in file opening" << endl;
        exit(1);
    }
    fin >> level >> hp >> atk >> def;
    fin.close();
}

//save the player to playerdata.txt
void Player::savePlayer() {
    ofstream fout;
    fout.open("playerdata.txt");
    if (fout.fail()) {
        cout << "Error in file opening" << endl;
        exit(1);
    }
    fout << level << endl;
    fout << hp << endl;
    fout << atk << endl;
    fout << def << endl;
    fout.close();
}