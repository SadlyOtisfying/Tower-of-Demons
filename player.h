#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    int x;
    int y;
    int level;
    int hp ;
    int atk;
    int def;
    void loadPlayer();
    void savePlayer();
};

#endif
