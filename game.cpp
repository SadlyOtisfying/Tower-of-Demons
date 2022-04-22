#include "player.h"
#include "tile.h"

#include <iostream>
#include <iomanip>

using namespace std;

//prompt the user for an integer with limited options
int prompt(string output, int options) {
    int ans;
    cout<<output;
    string input;
    cin>>input;
    try {
        ans = stoi(input);
        if(ans < 0 || ans >= options)
            throw 1;
    }
    catch (...) {
        cout<<"..... This is an invalid input. Are you challenging me? Bad choice ;) The last option will be chosen for you."<<endl;
        ans = options - 1;
    }
    return ans;
}

int main() {
    cout<<fixed<<setprecision(2);
    cout<<"Welcome to Tower of Demons!"<<endl;
    int diff = prompt("Please choose the difficulty (0 - easy; 1 - normal; 2 - hard): ", 3);
    cout<<"Your love, Princess Lily was captured by some demons and locked in the top of a tower. Now, save her. Good luck."<<endl;

}

