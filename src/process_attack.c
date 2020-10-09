#include "header.h"

void processAttack(Animated_Entity *gachi, Control *keyboard, Mix_Chunk *punchSound, Animated_Entity **enemies) {
    if (gachi->fight.HP < 0) gachi->fight.HP = 0;
    if (gachi->fight.HP == 0) {
        gachi->fight.attackT = 0;
        return;
    }
    if (keyboard->KEY_F) {
        if (gachi->fight.attackT == 0){
            gachi->fight.attackT = gachi->fight.baseAttackT;
        }
    }
    if (gachi->fight.attackT == gachi->fight.baseAttackT) {
        if (distance(gachi, enemies[0]) < gachi->fight.attackRange) {
            enemies[0]->fight.HP = enemies[0]->fight.HP - gachi->fight.damage;
            enemies[0]->fight.attacked = 5;
            if (enemies[0]->fight.HP < 0) enemies[0]->fight.HP = 0;
        }
        Mix_PlayChannel(3, punchSound, 0);
    }
    if (gachi->fight.attackT > 0)
        gachi->fight.attackT--;
}
