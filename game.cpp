#include "player.h"
#include "tile.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void initGame() {
    cout<<fixed<<setprecision(2);
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
        cout << "..... This is an invalid input. Are you challenging me? Bad choice ;) The last option has been chosen for you." << endl;
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

void printMap(vector<vector<vector<Tile>>> &map, int level) {
    for (int i=0;i<6;i++) {
        for (int j=0;j<6;j++) {
            if(map[level][i][j].visible) {
                if(map[level][i][j].type == "SPACE")
                    cout<<"."<<" ";
                else if(map[level][i][j].type == "POTION")
                    cout<<"P"<<" ";
                else if(map[level][i][j].type == "SWORD")
                    cout<<"S"<<" ";
                else if(map[level][i][j].type == "ARMOR")
                    cout<<"A"<<" ";
                else if(map[level][i][j].type == "DEMON")
                    cout<<"D"<<" ";
            }
            else
                cout<<"X"<<" ";
        }
        cout<<endl;
    }

}

void startGame() {
    cout << "Welcome to Tower of Demons!" << endl;

    // set difficulty and generate map
    int diff = prompt("Please choose the difficulty (0 - easy; 1 - normal; 2 - hard): ", 3);
    int levels = (diff + 1) * 2;
    vector<vector<vector<Tile>>> map;
    generateMap(map, levels);
    cout << "Your love, Princess Lily was captured by some demons and locked in the top of a tower. Now, save her. Good luck." << endl;

    // make player
    Player p;
    p.loadPlayer();

    // game loop
    while(p.level < levels) {
        cout<<"Your move: ";
        string move;
        cin>>move;
        for(char &c : move)
            c = tolower(c);
        if(move == "help") {

        }
        else if (move == "up" || move == "w") {

        }
        else if (move == "left" || move == "a") {

        }
        else if (move == "down" || move == "s") {

        }
        else if (move == "right" || move == "d") {

        }
        else if (move == "reset") {

        }
        else if (move == "exit") {
            
        }

    }

}



int main() {
    initGame();
    startGame();
}
