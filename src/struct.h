#pragma once
#include "header.h"

enum isPressed {
    unpressed,
    pressed,
};

enum color {
    white,
    grey,
    black,
    red,
};

enum state {
    peaceful, // покой
    run, // движение
    attack, // атака
};

typedef struct ctrl {
    bool KEY_W;
    bool KEY_A;
    bool KEY_S;
    bool KEY_D;
    bool KEY_Shift;
    bool KEY_Space;
    bool KEY_F;
} Control;

typedef struct mvm {
    int xP, yP;
    float x, y;
    float dx, dy;
    float xMS, yMS;
    float ax, ay;
    float timePrev;
    float MS, A;
    float xPrev, yPrev;
} Movement;

typedef struct ent {
    SDL_Texture *texture;
    SDL_Rect rect;
    Movement mvmnt;
} Entity;

typedef struct structure_for_animation {
    SDL_Texture **textures;
    int currTex, ticksPassed, state;
} Textures;

typedef struct structure_for_fight {
    int attackRange;
    int damage;
    int attackT;
    int baseAttackT;
    int HP;
    int attacked;
    float x, y;
} Fight;

typedef struct scr_vals {
    int agr_dst;
    int state;
    int timer;
} Script;

typedef struct anim_ent {
    Textures *textures;
    SDL_Rect rect;
    Movement mvmnt;
    Fight fight;
    Script vals;
} Animated_Entity;

typedef struct graph {
    struct graph *nodes;
    int dist;
    int color;
    SDL_Point pos;
} node;

// Data structure for stack
typedef struct stack {
    int maxsize;  // define max capacity of stack
    node *top;
    node **items;
} stack;
