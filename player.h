#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>

struct Player {
    int diff;
    int x = 0;
    int y = 0;
    int level;
    double hp;
    int atk;
    int def;
    time_t lastSaved;
    void load();
    void save();
    void reset();
};

#endif
