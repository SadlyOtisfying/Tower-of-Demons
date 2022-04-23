#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    int x = 0;
    int y = 0;
    int level = 0;
    double hp = 100;
    int atk = 2;
    int def = 2;
    void loadPlayer();
    void savePlayer();
    void reset();
};

#endif
