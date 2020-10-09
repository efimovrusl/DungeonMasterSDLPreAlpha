#include "header.h"

void processGachiAnimations(Animated_Entity* gachi) {
    int* ctx = &gachi->textures->currTex;
    int* tks = &gachi->textures->ticksPassed;
    int* ATTACK_TIME = &gachi->fight.baseAttackT;
    int* attack_timer = &gachi->fight.attackT;
    int direction = get_direction(gachi);
    if (closer_to_zero(gachi->mvmnt.dx, 3) == 0 && closer_to_zero(gachi->mvmnt.dy, 3) == 0) {
        direction = 90;
        *tks = 0;
    } 
    // MOVES
    (*tks)++;
    if (*tks > 10)
        *tks = 0, (*ctx)++;
    switch (direction / 45) {
        case 0: // 18 20
            if (*ctx < 24 || *ctx > 27)
                (*ctx) = 24;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 39;
                break;
        case 1: // 15 17
            if (*ctx < 20 || *ctx > 23)
                (*ctx) = 20;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 39;
                break;
        case 2:  // 0 2
            if (*ctx < 0 || *ctx > 3)
                (*ctx) = 0;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 33;
            break;
        case 3: // 9 11
            if (*ctx < 12 || *ctx > 15)
                (*ctx) = 12;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 33;
            break;
        case 4: // 6 8
            if (*ctx < 8 || *ctx > 11)
                (*ctx) = 8;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 35;
            break;
        case 5: // 3 5
            if (*ctx < 4 || *ctx > 7)
                (*ctx) = 4;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 35;
            break;
        case 6:  // 12 14
            if (*ctx < 16 || *ctx > 19)
                (*ctx) = 16;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 37;
            break;
        case 7: // 21 23
            if (*ctx < 28 || *ctx > 31)
                (*ctx) = 28;
            if (*attack_timer > *ATTACK_TIME - 7)
                (*ctx) = 37;
            break;
        default:
            *ctx = 1;
            break;
    }
    if (gachi->fight.HP <= 0) *ctx = 40; 
    int x = 0, y = 0;
    SDL_QueryTexture(gachi->textures->textures[*ctx], NULL, NULL, &x, &y);
    gachi->rect.w = gachi->rect.h / y * x;
    gachi->rect.x = SCREEN_WIDTH / 2 - gachi->rect.w / 2;
    // printf("%i %i\n", x, y);
}
