#ifndef CHANGER_H
#define CHANGER_H

#define PHASES 8
#define WALLS 4

typedef struct changer
{
    char* names[PHASES];
    int* walls[WALLS];
    int* layer2s[WALLS];
    int* grounds[WALLS];

} Changer;

Changer changer;

void init_changer(Changer* changer);


#endif