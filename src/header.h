#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"
#include "stack.h"

static const int SCREEN_WIDTH = 2560;
static const int SCREEN_HEIGHT = 1350;

static const float METER = (float)SCREEN_HEIGHT / 7;

void processControl(SDL_Event *e, Control *KeyBoard1, Mix_Chunk* walkSound);
void processMovement(Animated_Entity *entity, Control *keyboard, float *coords, unsigned int *collision, Mix_Chunk *ahSound);
float abs_f(float num);
void swap(void **v1, void **v2);
float closer_to_zero(float num, float step);
int isCloser(Animated_Entity *ent1, Animated_Entity *ent2);
int isLower(Animated_Entity *ent1, Animated_Entity *ent2);
void sortEnt(Animated_Entity **entities, int (*f)(Animated_Entity *, Animated_Entity *));
void getMapCoords(float x, float y, float *arr);
void getRealCords(float x, float y, float *arr);
SDL_Texture *loadTextureBpm(char *image, SDL_Renderer *rend);
Animated_Entity *new_A_Entity(SDL_Texture **sdl_textures, SDL_Renderer *rend, int height, int width, int xPrimary, int yPrimary, int max_speed, int acceleration);
Textures *new_Textures(SDL_Texture **textures);
float dCos(float i);
int get_direction(Animated_Entity *aEntity);
SDL_Texture **loadGachimanTexs(SDL_Renderer *rend);
SDL_Texture **loadNinjaTexs(SDL_Renderer *rend);
SDL_Texture **loadCreeperTexs(SDL_Renderer *rend);
void processGachiAnimations(Animated_Entity *gachi);
Animated_Entity *new_ENEMY(SDL_Texture **sdl_textures, SDL_Renderer *rend, int height, int width, int xPrimary, int yPrimary, int HP, int dmg, int timeForAttack);
void processCreeper(Animated_Entity *creeper, Animated_Entity *gachi, Entity *map, unsigned int *collision, Mix_Chunk *Alah, Mix_Chunk *Explosion);
void processNinja(Animated_Entity *ninja, Animated_Entity *gachi, Entity *map, unsigned int *collision, Mix_Chunk *);
void processAttack(Animated_Entity *gachi, Control *keyboard, Mix_Chunk *punchSound, Animated_Entity** enemies);
float distance(Animated_Entity *ent1, Animated_Entity *ent2);
