#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    int diff;
    int x;
    int y;
    int level;
    double hp;
    int atk;
    int def;
    void loadPlayer();
    void savePlayer();
    void reset();
};

#endif
