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

    void loadPlayer(int x, int y, int level, int hp, int atk, int def) {
        this->x = x;
        this->y = y;
        this->level = level;
        this->hp = hp;
        this->atk = atk;
        this->def = def;
    }
};