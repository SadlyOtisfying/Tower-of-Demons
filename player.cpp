#include <fstream>
#include <iostream>

using namespace std;

#define MAX_HP 100
#define DEFAULT_ATK 2
#define DEFAULT_DEF 2

struct Player {
    int x = 0;
    int y = 0;
    int level = 0;
    int hp = MAX_HP;
    int atk = DEFAULT_ATK;
    int def = DEFAULT_DEF;

    void loadPlayer() {
        ifstream fin;
        fin.open("playerdata.txt");
        if (fin.fail()) {
            cout << "Error in file opening" << endl;
            exit(1);
        }
        fin >> this->level >> this->hp >> this->atk >> this->def;
        fin.close();
    }

    void savePlayer() {
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

    Player() { 
        savePlayer();
    }
};