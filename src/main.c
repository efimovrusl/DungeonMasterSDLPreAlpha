#include "header.h"

Entity* new_Entity(char* name, SDL_Renderer* rend, int height, int width, int xPrimary, int yPrimary, int max_speed, int acceleration) {
    Entity* obj = (Entity*)malloc(sizeof(Entity));
    obj->texture = loadTextureBpm(name, rend);
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
    return obj;
}



// move everything in opposite side of hero
void processPosition(Entity *entity, Animated_Entity *hero) {
    entity->rect.x = entity->mvmnt.x - (hero->mvmnt.x - hero->mvmnt.xP);
    entity->rect.y = entity->mvmnt.y - (hero->mvmnt.y - hero->mvmnt.yP);
}

//////////MENU BUTTONS CHECK//////////

bool checkBigButton(int mousex, int mousey, double coeff1, double coeff2) {
    if(mousex < (SCREEN_WIDTH/2 + SCREEN_HEIGHT*0.15) 
        && mousex > (SCREEN_WIDTH/2 - SCREEN_HEIGHT*0.15) 
        && mousey < (SCREEN_HEIGHT*(double)coeff1) 
        && mousey > (SCREEN_HEIGHT*(double)coeff2)
        ) return true;
    return false;
}

bool checkSmallButton(int mousex, int mousey, double coeff1, double coeff2) {
    if(mousex < (SCREEN_HEIGHT*(double)coeff1) 
        && mousex > (SCREEN_HEIGHT*(double)coeff2)
        && mousey < (SCREEN_HEIGHT*0.95 + SCREEN_HEIGHT/28)
        && mousey > (SCREEN_HEIGHT*0.95 - SCREEN_HEIGHT/14 - SCREEN_HEIGHT/28)
        ) return true;
    return false;
}

//////////////////////////////////////

void gachi_restart() {
    float f_arr[2] = {0, 0};
    getRealCords(40, 480, f_arr);
}

int main () {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return 1;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Surface* screen_surface = NULL;

    SDL_Window* window = NULL;

    SDL_Event e;
    
    Control KeyBoard1 = { 0, 0, 0, 0, 0, 0, 0 };

    float f_arr[2] = {0, 0};

    bool quit = false;

    window = SDL_CreateWindow("SHITTY SHIT", 0, 0,
             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        return 1;
    }
    unsigned int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);
    if (!rend) {
        printf("Prosnis ti obosralsa (rend)%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Texture* background = loadTextureBpm("resource/back_g.bmp", rend);

    int amount_of_enemies = 3;
    Animated_Entity** enemies = (Animated_Entity**)malloc(sizeof(Animated_Entity*) * amount_of_enemies + 1);
    enemies[amount_of_enemies] = NULL;
    Animated_Entity** entities = (Animated_Entity**)malloc(sizeof(Animated_Entity*) * amount_of_enemies + 2);
    entities[amount_of_enemies + 1] = NULL;

    Animated_Entity* gachiMan = new_A_Entity(loadGachimanTexs(rend), rend, 2 * METER, 0.75 * METER,
                                                 SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 9 * METER, METER / 7);
    entities[amount_of_enemies] = gachiMan;
    
    // (139, 424)
    f_arr[0] = 0, f_arr[1] = 0;
    getRealCords(139 - 40, 424 - 480, f_arr);
    Animated_Entity* ninja1 = new_ENEMY(loadNinjaTexs(rend), rend, 1.5 * METER, 0.5 * METER,
                                        SCREEN_WIDTH / 2 + f_arr[0], SCREEN_HEIGHT / 2 + f_arr[1], 100, 15, 120);
    ninja1->fight.HP = 10;
    getRealCords(136 - 40, 424 - 480, f_arr);
    Animated_Entity* creeper1 = new_ENEMY(loadCreeperTexs(rend), rend, 1.8 * METER, 0.8 * METER,
                                          SCREEN_WIDTH / 2 + f_arr[0], SCREEN_HEIGHT / 2 + f_arr[1], 100, 50, 120);
    getRealCords(234 - 40, 424 - 480, f_arr);
    Animated_Entity* creeper2 = new_ENEMY(loadCreeperTexs(rend), rend, 1.8 * METER, 0.8 * METER,
                                          SCREEN_WIDTH / 2 + f_arr[0], SCREEN_HEIGHT / 2 + f_arr[1], 100, 50, 120);
                                          getRealCords(234 - 40, 424 - 480, f_arr);

    enemies[0] = entities[0] = ninja1;
    enemies[1] = entities[1] = creeper1;
    enemies[2] = entities[2] = creeper2;

    f_arr[0] = 0, f_arr[1] = 0;
    getRealCords(40, 480, f_arr);
    Entity* map1_collision = new_Entity("resource/map/map1_collision.bmp", rend, 55 * METER, 55 * METER,
                                        -f_arr[0] + SCREEN_WIDTH / 2, -f_arr[1] + METER + SCREEN_HEIGHT / 2, 0, 0);
    Entity* map1_texture = new_Entity("resource/map/map1_texture.bmp", rend, 55 * METER, 55 * METER,
                                      -f_arr[0] + SCREEN_WIDTH / 2, -f_arr[1] + METER + SCREEN_HEIGHT / 2, 0, 0);
    f_arr[0] = 0, f_arr[1] = 0;

    Entity* map1_floor = new_Entity("resource/map/floor.bmp", rend, 55 * METER, 55 * METER,
                                        -f_arr[0] + SCREEN_WIDTH / 2, -f_arr[1] + METER + SCREEN_HEIGHT / 2, 0, 0);
    Entity* map1_back = new_Entity("resource/map/back.bmp", rend, 55 * METER, 55 * METER,
                                        -f_arr[0] + SCREEN_WIDTH / 2, -f_arr[1] + METER + SCREEN_HEIGHT / 2, 0, 0);
    Entity* map1_front = new_Entity("resource/map/front.bmp", rend, 55 * METER, 55 * METER,
                                        -f_arr[0] + SCREEN_WIDTH / 2, -f_arr[1] + METER + SCREEN_HEIGHT / 2, 0, 0);
    ///HEALTH///

    Entity* health_background = new_Entity("resource/health/health_background.bmp", rend, SCREEN_HEIGHT/7, 
    (SCREEN_HEIGHT/7) * 7, SCREEN_HEIGHT*0.15, SCREEN_HEIGHT*0.1, 0, 0);
    Entity* health_border = new_Entity("resource/health/health_border_gray.bmp", rend, SCREEN_HEIGHT/7, 
    (SCREEN_HEIGHT/7) * 4, SCREEN_HEIGHT*0.35, SCREEN_HEIGHT*0.1, 0, 0);
    Entity* health_rect = new_Entity("resource/health/health_rect.bmp", rend, SCREEN_HEIGHT/7, 
    (SCREEN_HEIGHT/7) * 7, SCREEN_HEIGHT*0.15, SCREEN_HEIGHT*0.1, 0, 0);

    ////////////
    Entity* gachiManFRONT = new_Entity("resource/gachiMan1.bmp", rend, 2 * METER, 0.75 * METER,
                                  SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.35, 9 * METER, METER / 7);
    Entity* boot = new_Entity("resource/enemy/boot.bmp", rend, SCREEN_HEIGHT*0.9, SCREEN_HEIGHT*0.5, SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 0, 0);
    Entity* blood_boot = new_Entity("resource/enemy/blood_boot.bmp", rend, SCREEN_HEIGHT*1, SCREEN_HEIGHT*0.5, SCREEN_WIDTH/2, SCREEN_HEIGHT/12, 0, 0);
    SDL_Texture* brick_wall = loadTextureBpm("resource/map_room.bmp", rend);
    ////////////

    Entity* button_continue = new_Entity("resource/buttons/Continue_Button.bmp", rend, SCREEN_HEIGHT/10, (SCREEN_HEIGHT/10) * 3, SCREEN_WIDTH/2, SCREEN_HEIGHT/4, 0, 0);
    Entity* button_new_game = new_Entity("resource/buttons/New_game_Button.bmp", rend, SCREEN_HEIGHT/10, (SCREEN_HEIGHT/10) * 3, SCREEN_WIDTH/2, SCREEN_HEIGHT/4 + SCREEN_HEIGHT/6, 0, 0);
    Entity* button_load = new_Entity("resource/buttons/Load_Button.bmp", rend, SCREEN_HEIGHT/10, (SCREEN_HEIGHT/10) * 3, SCREEN_WIDTH/2, SCREEN_HEIGHT/4 + SCREEN_HEIGHT/3, 0, 0);
    Entity* button_exit = new_Entity("resource/buttons/Quit_Button.bmp", rend, SCREEN_HEIGHT/10, (SCREEN_HEIGHT/10) * 3, SCREEN_WIDTH/2, SCREEN_HEIGHT/4 + SCREEN_HEIGHT/2, 0, 0);
    Entity* button_audio_on = new_Entity("resource/buttons/AudioOnButton.bmp", rend, SCREEN_HEIGHT/14, SCREEN_HEIGHT/14, SCREEN_HEIGHT/14, SCREEN_HEIGHT*0.95, 0, 0);
    Entity* button_audio_off = new_Entity("resource/buttons/AudioOffButton.bmp", rend, SCREEN_HEIGHT/14, SCREEN_HEIGHT/14, SCREEN_HEIGHT/14, SCREEN_HEIGHT*0.95, 0, 0);
    Entity* button_options = new_Entity("resource/buttons/Settings-Square-Button.bmp", rend, SCREEN_HEIGHT/14, SCREEN_HEIGHT/14, SCREEN_HEIGHT/6, SCREEN_HEIGHT*0.95, 0, 0);
    Entity* CommingSoon = new_Entity("resource/buttons/ComingSoon.bmp", rend, SCREEN_HEIGHT/16, (SCREEN_HEIGHT/12), SCREEN_WIDTH/2 - (SCREEN_HEIGHT/8.5), SCREEN_HEIGHT/4 + SCREEN_HEIGHT/3 - SCREEN_HEIGHT/25, 0, 0);
    Entity* CommingSoon2 = new_Entity("resource/buttons/ComingSoon.bmp", rend, SCREEN_HEIGHT/32, (SCREEN_HEIGHT/24), SCREEN_HEIGHT/6 - SCREEN_HEIGHT/36, SCREEN_HEIGHT*0.95 - SCREEN_HEIGHT/24 + SCREEN_HEIGHT/56, 0, 0);

    SDL_Surface* map1_surface = SDL_LoadBMP("resource/map/map1_collision.bmp");
    unsigned int *pixels = map1_surface->pixels;

    ///////LOAD MUS///////
    Mix_Music *backgroundSound = Mix_LoadMUS("resource/audio/Music1.wav");
    Mix_Music *Rasputin = Mix_LoadMUS("resource/audio/rasputin.wav");
    Mix_Chunk *ahSound = Mix_LoadWAV("resource/audio/ah.wav"); 
    Mix_Chunk *walkSound = Mix_LoadWAV("resource/audio/walk.wav");
    Mix_Chunk *punchSound = Mix_LoadWAV("resource/audio/Punch.wav");
    Mix_Chunk *Alah = Mix_LoadWAV("resource/audio/Alah.wav");
    Mix_Chunk *Explosion = Mix_LoadWAV("resource/audio/Explosion.wav");
    Mix_Chunk *ninja_attack = Mix_LoadWAV("resource/audio/ninja_attack.wav");
    //////////////////////
    Mix_PlayMusic(backgroundSound, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_VolumeChunk(ahSound, MIX_MAX_VOLUME/2);
    Mix_VolumeChunk(walkSound, MIX_MAX_VOLUME);
    Mix_VolumeChunk(punchSound, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(Alah, MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(Explosion, MIX_MAX_VOLUME/2);
    Mix_VolumeChunk(ninja_attack, MIX_MAX_VOLUME/2);
    SDL_RenderClear(rend);
    // draw to the window
    SDL_RenderCopy(rend, background, NULL, NULL);
    SDL_RenderPresent(rend);

    screen_surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(1000);
    
    bool GameStarted = 0, coming_soon = 0, coming_soon2 = 0, audioON = 1;
    int GameMode = 0;
    while (!quit){

        while (GameMode == 0) {
            while (SDL_PollEvent(&e)) {
                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);
                //  printf("%i || %i\n", mousex, mousey);
                //  printf("%f WW %f\n", SCREEN_WIDTH/2 + SCREEN_HEIGHT*0.15, SCREEN_WIDTH/2 - SCREEN_HEIGHT*0.15);
                //  printf("%f HH %f\n", SCREEN_HEIGHT * ((double)28/60), SCREEN_HEIGHT*((double)22/60));
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&mousex, &mousey);
                    if(GameStarted && checkBigButton(mousex, mousey, (double)18/60, (double)12/60)) {
                        //CONTINUE (CURRENT GAME)
                        GameMode = 1;
                    } else if(checkBigButton(mousex, mousey, (double)28/60, (double)22/60)) {
                        //RESTART (NEW GAME)
                        GameMode = 1;

                        gachiMan->mvmnt.x = gachiMan->mvmnt.xP;
                        gachiMan->mvmnt.y = gachiMan->mvmnt.yP;
                        gachiMan->fight.HP = 100;
                        creeper1->fight.HP = 100;
                        creeper1->textures->currTex = 0;
                        creeper1->vals.state = 0;
                        creeper1->mvmnt.x = creeper1->mvmnt.xP;
                        creeper1->mvmnt.y = creeper1->mvmnt.yP;
                        creeper2->fight.HP = 100;
                        creeper2->textures->currTex = 0;
                        creeper2->vals.state = 0;
                        creeper2->mvmnt.x = creeper2->mvmnt.xP;
                        creeper2->mvmnt.y = creeper2->mvmnt.yP;
                        ninja1->fight.HP = 10;
                        ninja1->textures->currTex = 0;
                        ninja1->vals.state = 0;
                        ninja1->mvmnt.x = ninja1->mvmnt.xP;
                        ninja1->mvmnt.y = ninja1->mvmnt.yP;

                    } else if(checkBigButton(mousex, mousey, (double)38/60, (double)32/60)) {
                        //LOAD SAVE (COMING SOON)
                        if(!coming_soon)coming_soon = 1;
                        else coming_soon = 0;
                    } else if(checkBigButton(mousex, mousey, (double)48/12, (double)42/60)) {
                        //QUIT (EXIT GAME)
                        quit = true;
                        GameMode = -1;
                    } else if(checkSmallButton(mousex, mousey, (double)3/28, (double)1/28)) {
                        //SOUND (GAME MUSIC)
                        if(!audioON) {
                            audioON = 1;
                            Mix_VolumeMusic(MIX_MAX_VOLUME/4);
                            Mix_VolumeChunk(ahSound, MIX_MAX_VOLUME/2);
                            Mix_VolumeChunk(walkSound, MIX_MAX_VOLUME);
                            Mix_VolumeChunk(punchSound, MIX_MAX_VOLUME/4);
                            Mix_VolumeChunk(Alah, MIX_MAX_VOLUME/8);
                            Mix_VolumeChunk(Explosion, MIX_MAX_VOLUME/2);
                        }
                        else {
                            audioON = 0;
                            Mix_VolumeMusic(0);
                            Mix_VolumeChunk(ahSound, 0);
                            Mix_VolumeChunk(walkSound, 0);
                            Mix_VolumeChunk(punchSound, 0);
                            Mix_VolumeChunk(Alah, 0);
                            Mix_VolumeChunk(Explosion, 0);
                        }
                    } else if(checkSmallButton(mousex, mousey, (double)3/12, (double)1/12)) {
                        //OPTIONS (COMING SOON 2)
                        if(!coming_soon2)coming_soon2 = 1;
                        else coming_soon2 = 0;
                    }
                }
                if (e.type == SDL_QUIT) {
                    quit = true, GameMode = -1;
                }
            }
            // render copy buttons and text
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, background, NULL, NULL);
            if(GameStarted) SDL_RenderCopy(rend, button_continue->texture, NULL, &button_continue->rect);
            SDL_RenderCopy(rend, button_new_game->texture, NULL, &button_new_game->rect);
            SDL_RenderCopy(rend, button_load->texture, NULL, &button_load->rect);
            SDL_RenderCopy(rend, button_exit->texture, NULL, &button_exit->rect);
            if(audioON) SDL_RenderCopy(rend, button_audio_on->texture, NULL, &button_audio_on->rect);
            else SDL_RenderCopy(rend, button_audio_off->texture, NULL, &button_audio_off->rect);
            SDL_RenderCopy(rend, button_options->texture, NULL, &button_options->rect);
            if(coming_soon) SDL_RenderCopy(rend, CommingSoon->texture, NULL, &CommingSoon->rect);
            if(coming_soon2) SDL_RenderCopy(rend, CommingSoon2->texture, NULL, &CommingSoon2->rect);
            SDL_RenderPresent(rend);
            if(GameMode == 1) GameStarted = 1;
        }

        while(GameMode == 1) {
            while (SDL_PollEvent(&e)) {
                // get time
                // unsigned long beginning = clock();
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            GameMode = 0;
                            break;
                        default: break;
                    }
                }
                processControl(&e, &KeyBoard1, walkSound);
            }
            SDL_RenderClear(rend);
            getMapCoords(gachiMan->mvmnt.x - map1_collision->mvmnt.xP,
                        gachiMan->mvmnt.y - map1_collision->mvmnt.yP + METER, f_arr);
            processMovement(gachiMan, &KeyBoard1, f_arr, pixels, ahSound);
            processPosition(map1_collision, gachiMan);
            processPosition(ninja1, gachiMan);
            processPosition(creeper1, gachiMan);
            processPosition(creeper2, gachiMan);
            processPosition(map1_texture, gachiMan);
            sortEnt(enemies, isCloser);
            processAttack(gachiMan, &KeyBoard1, punchSound, enemies);
            processGachiAnimations(gachiMan);

            // Creating the rectangle
            SDL_RenderCopy(rend, background, NULL, NULL);
            //SDL_RenderCopy(rend, map1_collision->texture, NULL, &map1_collision->rect);

            SDL_RenderCopy(rend, map1_floor->texture, NULL, &map1_texture->rect);
            SDL_RenderCopy(rend, map1_back->texture, NULL, &map1_texture->rect);

            processCreeper(creeper1, gachiMan, map1_collision, pixels, Alah, Explosion);
            processCreeper(creeper2, gachiMan, map1_collision, pixels, Alah, Explosion);
            processNinja(ninja1, gachiMan, map1_collision, pixels, ninja_attack);
            // SDL_RenderFillRect(rend, &movable);
            sortEnt(entities, isLower);
            for (int i = 0; i < amount_of_enemies + 1; i++)
                SDL_RenderCopy(rend, entities[i]->textures->textures[entities[i]->textures->currTex], NULL, &(entities[i]->rect));
            SDL_RenderCopy(rend, map1_front->texture, NULL, &map1_texture->rect);

            SDL_RenderCopy(rend, health_background->texture, NULL, &health_background->rect);
            SDL_RenderCopy(rend, health_rect->texture, NULL, &health_rect->rect);
            SDL_RenderCopy(rend, health_border->texture, NULL, &health_border->rect);
            if ((gachiMan->mvmnt.x > 8825 && gachiMan->mvmnt.x < 9400) && 
                (gachiMan->mvmnt.y < -378 && gachiMan->mvmnt.y > -940)) {
                GameMode = 2;
                Mix_PlayMusic(Rasputin, -1);
            }
            SDL_RenderPresent(rend);

        }
        int i = 0;
        while (GameMode == 2) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                    GameMode = -1;
                }
                if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                    GameMode = -1;
                }
            }
            if (!Mix_PlayingMusic())Mix_PlayMusic(Rasputin, -1);
            for (; i < 10; i++) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, brick_wall, NULL, NULL);
                SDL_RenderCopy(rend, gachiManFRONT->texture, NULL, &gachiManFRONT->rect);
                if(i < 9)SDL_RenderCopy(rend, boot->texture, NULL, &boot->rect);
                if(i == 9) SDL_RenderCopy(rend, blood_boot->texture, NULL, &boot->rect);
                SDL_RenderPresent(rend);
                if(i == 0) SDL_Delay(1000);
                SDL_Delay(50);
                boot->rect.y += 100;
            }
        }
    }
    
    SDL_DestroyWindow(window);

    Mix_FreeMusic(backgroundSound);
    Mix_CloseAudio();
    SDL_Quit();
    

    return 0;
}
