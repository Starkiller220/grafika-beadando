#include "changer.h"
#include "model.h"

void init_changer(Changer* changer)
{
    

    char* names[PHASES] = {
            "textures//blue.jpg",
            "textures//red.jpg",
            "textures//yellow.jpg",
            "textures//green.jpg",
            "textures//pink.jpg",
            "textures//brown.jpg",
            "textures//orange.jpg",
            "textures//purple.jpg",
        };
    
    changer->walls[0] = &world.room.middle4;
    changer->walls[1] = &world.room.middle;
    changer->walls[2] = &world.room.middle2;
    changer->walls[3] = &world.room.middle3;

    changer->grounds[0] = &world.room.ground;
    changer->grounds[1] = &world.room.ground2;
    changer->grounds[2] = &world.room.ground3;
    changer->grounds[3] = &world.room.ground4;

    changer->layer2s[0] = &world.room.middlel2;
    changer->layer2s[1] = &world.room.middle2l2;
    changer->layer2s[2] = &world.room.middle3l2;
    changer->layer2s[3] = &world.room.middle4l2;

    

    for(int i = 0; i < PHASES;i++){
        changer->names[i] = names[i]; 
    }
}
