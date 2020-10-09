#include "header.h"

void processCreeper(Animated_Entity *creeper, Animated_Entity *gachi, Entity *map, unsigned int *collision, Mix_Chunk* Alah, Mix_Chunk* Explosion) {
    float f_arr[2] = {0, 0};
    int *state = &creeper->vals.state;
    getMapCoords(creeper->rect.x + creeper->rect.w / 2 - map->rect.x,
                 creeper->rect.y + creeper->rect.h / 2 - map->rect.y + METER, f_arr);
    if (creeper->fight.HP == 0) {
        *state = 6;
        creeper->vals.timer = 0;
    }
    switch (*state) {
        case 0:
            creeper->textures->currTex = 0;
            if (creeper->fight.attacked > 0) {
                creeper->fight.attacked--;
                creeper->textures->currTex = 4;
            }
            if (distance(creeper, gachi) < 1000)
                *state = 1;
            else
                break;
        case 1: // move down
            creeper->textures->currTex = 0;
            if (creeper->fight.attacked > 0) {
                creeper->fight.attacked--;
                creeper->textures->currTex = 4;
            }
            if (collision[(int)round(f_arr[0]) + (int)(round(f_arr[1]) + 0.06 * METER) * 500] == 0) {
                creeper->mvmnt.y += 10;
                break;
            } else {
                *state = 2;
            }
        case 2: // move to gachi in coridor
            if (distance(creeper, gachi) < 1000) {
                if (creeper->mvmnt.x > gachi->mvmnt.x) {
                    creeper->mvmnt.x -= distance(creeper, gachi) / 50 + 2;
                    creeper->textures->currTex = 1;
                    if (creeper->fight.attacked > 0) {
                        creeper->fight.attacked--;
                        creeper->textures->currTex = 5;
                    }
                }
                else {
                    creeper->mvmnt.x += distance(creeper, gachi) / 50 + 2;
                    creeper->textures->currTex = 3;
                    if (creeper->fight.attacked > 0) {
                        creeper->fight.attacked--;
                        creeper->textures->currTex = 7;
                    }
                }
                if (sqrtf(powf(creeper->mvmnt.xP - creeper->mvmnt.x, 2) + powf(creeper->mvmnt.yP - creeper->mvmnt.y, 2)) > 1000)
                    *state = 4;
            }
            if (distance(creeper, gachi) <= 300) {
                *state = 3;
                creeper->vals.timer = 50;
            }
            break;
        case 3: // begin explosion
            if(!Mix_Playing(4)) Mix_PlayChannel(4, Alah, 0);
            if (creeper->vals.timer > 0)
                creeper->vals.timer--;
            if (distance(creeper, gachi) > 60) {
                if (creeper->mvmnt.x > gachi->mvmnt.x) {
                    creeper->mvmnt.x -= distance(creeper, gachi) / 40;
                    creeper->textures->currTex = 1;
                    if (creeper->fight.attacked > 0) {
                        creeper->fight.attacked--;
                        creeper->textures->currTex = 5;
                    }
                } else {
                    creeper->mvmnt.x += distance(creeper, gachi) / 40;
                    creeper->textures->currTex = 3;
                    if (creeper->fight.attacked > 0) {
                        creeper->fight.attacked--;
                        creeper->textures->currTex = 7;
                    }
                }
            }
            if (distance(creeper, gachi) > 300) {
                *state = 2;
                creeper->vals.timer = 0;
                break;
            }
            if (creeper->vals.timer <= 8) {
                creeper->textures->currTex = 8;
                *state = 6;
            }
            break;
        case 4: // run away
            if (distance(creeper, gachi) < 800 && abs_f(creeper->mvmnt.x - creeper->mvmnt.xP) < 200) {
                *state = 2;
                break;
            }
            if (closer_to_zero(creeper->mvmnt.x - creeper->mvmnt.xP, 5) != 0) {
                if (creeper->mvmnt.x > creeper->mvmnt.xP) {
                    creeper->mvmnt.x -= 5;
                    creeper->textures->currTex = 1;
                    if (creeper->fight.attacked > 0) {
                        creeper->fight.attacked--;
                        creeper->textures->currTex = 5;
                    }
                }
                if (creeper->mvmnt.x < creeper->mvmnt.xP) {
                    creeper->mvmnt.x += 5;
                    creeper->textures->currTex = 3;
                    if (creeper->fight.attacked > 0) {
                        creeper->fight.attacked--;
                        creeper->textures->currTex = 7;
                    }
                }
                break;
            } else
                *state = 5; // run to init pos
        case 5: // run back to room
            if (creeper->mvmnt.y - creeper->mvmnt.yP > 0) {
                creeper->textures->currTex = 2;
                if (creeper->fight.attacked > 0) {
                    creeper->fight.attacked--;
                    creeper->textures->currTex = 6;
                }
                creeper->mvmnt.y -= 5;
            } else *state = 0;
            break;
        case 6:
            if (creeper->vals.timer > 0) {
                creeper->textures->currTex = 8;
                if (creeper->vals.timer == 8) 
                    gachi->fight.HP -= creeper->fight.damage;
                creeper->vals.timer--;
                if (creeper->vals.timer == 0) {
                    if(!Mix_Playing(5)) Mix_PlayChannel(5, Explosion, 0);
                }
                break;
            }
            creeper->textures->currTex = 9;
            break;
    }
    int x = 0, y = 0;
    SDL_QueryTexture(creeper->textures->textures[creeper->textures->currTex], NULL, NULL, &x, &y);
    creeper->rect.w = creeper->rect.h / y * x;
    creeper->rect.x = creeper->rect.x - creeper->rect.w / 2;
}

void processNinja(Animated_Entity *ninja, Animated_Entity *gachi, Entity *map, unsigned int *collision, Mix_Chunk* ninja_attack) {
    int x = 0, y = 0;
    float f_arr[2] = {0, 0};
    int *state = &ninja->vals.state;
    getMapCoords(ninja->rect.x + ninja->rect.w / 2 - map->rect.x,
                 ninja->rect.y + ninja->rect.h / 2 - map->rect.y + METER, f_arr);
    if (ninja->fight.HP <= 0) {
        ninja->textures->currTex = 8;
        return;
    }
    switch (*state) {
        case 0:  // if sees gachi
            ninja->textures->currTex = 0;
            if (distance(ninja, gachi) < 1000)
                *state = 1;
            else
                break;
        case 1:  // go to coridor
            ninja->textures->currTex = 0;
            if (collision[(int)round(f_arr[0]) + (int)(round(f_arr[1]) + 0.12 * METER) * 500] == 0) {
                ninja->mvmnt.y += 10;
                break;
            } else {
                *state = 2;
            }
        case 2: // attack trigger
            if (distance(ninja, gachi) > 600)
                break;
            else {
                ninja->fight.x = ninja->mvmnt.x;
                ninja->fight.y = ninja->mvmnt.y;
                ninja->vals.timer = 80;
                ninja->textures->currTex = 9;
                *state = 3;
            }
        case 3: // attack
            ninja->vals.timer--;
            if (ninja->vals.timer == 60) {
                ninja->mvmnt.x = gachi->mvmnt.x;
                ninja->mvmnt.y = gachi->mvmnt.y - 0.72 * METER;
                if (ninja->mvmnt.x > gachi->mvmnt.x)
                    ninja->textures->currTex = 3;
                else ninja->textures->currTex = 1;
            }
            if (ninja->vals.timer == 40) {
                gachi->fight.HP = gachi->fight.HP - ninja->fight.damage;
                ninja->textures->currTex = 9;
            }
            if (ninja->vals.timer == 20) {
                Mix_PlayChannel(6, ninja_attack, 0);
                ninja->mvmnt.x = ninja->fight.x;
                ninja->mvmnt.y = ninja->fight.y;
                ninja->textures->currTex = 2;
            }
            if (ninja->vals.timer == 0) {
                *state = 4;
            }
            break;
        case 4: // return back
            ninja->textures->currTex = 2;
            ninja->mvmnt.y -= 10;
            if (closer_to_zero(ninja->mvmnt.y - ninja->mvmnt.yP, 10) == 0) {
                ninja->mvmnt.x = ninja->mvmnt.xP;
                ninja->mvmnt.y = ninja->mvmnt.yP;
                *state = 0;
            } else break;

        default:
            break;
    }
    SDL_QueryTexture(ninja->textures->textures[ninja->textures->currTex], NULL, NULL, &x, &y);
    ninja->rect.w = ninja->rect.h / y * x;
    ninja->rect.x = ninja->rect.x - ninja->rect.w / 2;
}
