#include "header.h"

Animated_Entity* new_A_Entity(SDL_Texture** sdl_textures, SDL_Renderer* rend, int height, int width, int xPrimary, int yPrimary, int max_speed, int acceleration) {
    Animated_Entity* obj = (Animated_Entity*)malloc(sizeof(Animated_Entity));
    obj->textures = new_Textures(sdl_textures);
    obj->rect.h = height;
    obj->rect.w = width;
    obj->rect.x = xPrimary - width / 2;
    obj->rect.y = yPrimary - height / 2;
    obj->mvmnt.dx = 0;
    obj->mvmnt.dy = 0;
    obj->mvmnt.timePrev = clock();
    obj->mvmnt.xMS = 0;
    obj->mvmnt.yMS = 0;
    obj->mvmnt.ax = 0;
    obj->mvmnt.ay = 0;
    obj->mvmnt.MS = max_speed;
    obj->mvmnt.A = acceleration;
    obj->mvmnt.x = xPrimary;
    obj->mvmnt.y = yPrimary;
    obj->mvmnt.xP = xPrimary;
    obj->mvmnt.yP = yPrimary;
    obj->mvmnt.xPrev = xPrimary;
    obj->mvmnt.yPrev = yPrimary;
    obj->fight.attackRange = 200;
    obj->fight.attackT = 0;
    obj->fight.baseAttackT = 30;
    obj->fight.HP = 100;
    obj->fight.attacked = 0;
    obj->fight.damage = 20;
    obj->fight.x = 0;
    obj->fight.y = 0;
    return obj;
}

Animated_Entity* new_ENEMY(SDL_Texture** sdl_textures, SDL_Renderer* rend, int height, int width, int xPrimary, int yPrimary, int HP, int dmg, int timeForAttack) {
    Animated_Entity* obj = (Animated_Entity*)malloc(sizeof(Animated_Entity));
    obj->textures = new_Textures(sdl_textures);
    obj->rect.h = height;
    obj->rect.w = width;
    obj->rect.x = xPrimary - width / 2;
    obj->rect.y = yPrimary - height / 2;
    obj->mvmnt.dx = 0;
    obj->mvmnt.dy = 0;
    obj->mvmnt.timePrev = clock();
    obj->mvmnt.xMS = 0;
    obj->mvmnt.yMS = 0;
    obj->mvmnt.ax = 0;
    obj->mvmnt.ay = 0;
    obj->mvmnt.MS = 0;
    obj->mvmnt.A = 0;
    obj->mvmnt.x = xPrimary;
    obj->mvmnt.y = yPrimary;
    obj->mvmnt.xP = xPrimary;
    obj->mvmnt.yP = yPrimary;
    obj->mvmnt.xPrev = xPrimary;
    obj->mvmnt.yPrev = yPrimary;
    obj->fight.damage = dmg;
    obj->fight.attackT = 0;
    obj->fight.baseAttackT = timeForAttack;
    obj->fight.HP = HP;
    obj->vals.agr_dst = 1000;
    obj->vals.state = 0;
    obj->vals.timer = 0;
    return obj;
}

Textures* new_Textures(SDL_Texture** textures) {
    Textures *texs = (Textures*)malloc(sizeof(Textures));
    texs->textures = textures;
    texs->currTex = 0;
    texs->state = peaceful;
    texs->ticksPassed = 0;
    return texs;
}
