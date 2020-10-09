#include "header.h"

SDL_Texture** loadGachimanTexs(SDL_Renderer *rend) {
    SDL_Texture** arr = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 41);
    arr[0] = loadTextureBpm("resource/gachiMan/guchi_down1.bmp", rend);
    arr[1] = loadTextureBpm("resource/gachiMan/guchi_down2.bmp", rend);
    arr[2] = arr[0];
    arr[3] = loadTextureBpm("resource/gachiMan/guchi_down3.bmp", rend);

    arr[4] = loadTextureBpm("resource/gachiMan/guchi_up_left1.bmp", rend);
    arr[5] = loadTextureBpm("resource/gachiMan/guchi_up_left2.bmp", rend);
    arr[6] = arr[4];
    arr[7] = loadTextureBpm("resource/gachiMan/guchi_up_left3.bmp", rend);

    arr[8] = loadTextureBpm("resource/gachiMan/guchi_left1.bmp", rend);
    arr[9] = loadTextureBpm("resource/gachiMan/guchi_left2.bmp", rend);
    arr[10] = arr[8];
    arr[11] = loadTextureBpm("resource/gachiMan/guchi_left3.bmp", rend);

    arr[12] = loadTextureBpm("resource/gachiMan/guchi_down_left1.bmp", rend);
    arr[13] = loadTextureBpm("resource/gachiMan/guchi_down_left2.bmp", rend);
    arr[14] = arr[12];
    arr[15] = loadTextureBpm("resource/gachiMan/guchi_down_left3.bmp", rend);

    arr[16] = loadTextureBpm("resource/gachiMan/guchi_up1.bmp", rend);
    arr[17] = loadTextureBpm("resource/gachiMan/guchi_up2.bmp", rend);
    arr[18] = arr[16];
    arr[19] = loadTextureBpm("resource/gachiMan/guchi_up3.bmp", rend);

    arr[20] = loadTextureBpm("resource/gachiMan/guchi_down_right1.bmp", rend);
    arr[21] = loadTextureBpm("resource/gachiMan/guchi_down_right2.bmp", rend);
    arr[22] = arr[20];
    arr[23] = loadTextureBpm("resource/gachiMan/guchi_down_right3.bmp", rend);

    arr[24] = loadTextureBpm("resource/gachiMan/guchi_right1.bmp", rend);
    arr[25] = loadTextureBpm("resource/gachiMan/guchi_right2.bmp", rend);
    arr[26] = arr[24];
    arr[27] = loadTextureBpm("resource/gachiMan/guchi_right3.bmp", rend);

    arr[28] = loadTextureBpm("resource/gachiMan/guchi_up_right1.bmp", rend);
    arr[29] = loadTextureBpm("resource/gachiMan/guchi_up_right2.bmp", rend);
    arr[30] = arr[28];
    arr[31] = loadTextureBpm("resource/gachiMan/guchi_up_right3.bmp", rend);
    /**
     *  FIGHTING
     */
    arr[32] = loadTextureBpm("resource/gachiMan/guchi_fight_down1.bmp", rend);
    arr[33] = loadTextureBpm("resource/gachiMan/guchi_fight_down2.bmp", rend);

    arr[34] = loadTextureBpm("resource/gachiMan/guchi_fight_left1.bmp", rend);
    arr[35] = loadTextureBpm("resource/gachiMan/guchi_fight_left2.bmp", rend);

    arr[36] = loadTextureBpm("resource/gachiMan/guchi_fight_up1.bmp", rend);
    arr[37] = loadTextureBpm("resource/gachiMan/guchi_fight_up2.bmp", rend);

    arr[38] = loadTextureBpm("resource/gachiMan/guchi_fight_right1.bmp", rend);
    arr[39] = loadTextureBpm("resource/gachiMan/guchi_fight_right2.bmp", rend);

    arr[40] = loadTextureBpm("resource/gachiMan/guchi_death1.bmp", rend);

    return arr;
}

SDL_Texture** loadCreeperTexs(SDL_Renderer* rend) {
    SDL_Texture** arr = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
    // down
    arr[0] = loadTextureBpm("resource/enemy/Enemy2_1.bmp", rend);
    // left
    arr[1] = loadTextureBpm("resource/enemy/Enemy2_4.bmp", rend);
    // up
    arr[2] = loadTextureBpm("resource/enemy/Enemy2_2.bmp", rend);
    // right
    arr[3] = loadTextureBpm("resource/enemy/Enemy2_3.bmp", rend);
    // down attacked
    arr[4] = loadTextureBpm("resource/enemy/Enemy2_5.bmp", rend);
    // left attacked
    arr[5] = loadTextureBpm("resource/enemy/Enemy2_8.bmp", rend);
    // up attacked
    arr[6] = loadTextureBpm("resource/enemy/Enemy2_6.bmp", rend);
    // right attacked
    arr[7] = loadTextureBpm("resource/enemy/Enemy2_7.bmp", rend);
    // BANG!!!!
    arr[8] = loadTextureBpm("resource/enemy/Enemy2_9.bmp", rend);
    // DEATH
    arr[9] = loadTextureBpm("resource/enemy/Enemy2_10.bmp", rend);

    return arr;
}

SDL_Texture** loadNinjaTexs(SDL_Renderer* rend) {
    SDL_Texture** arr = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 9);
    // down
    arr[0] = loadTextureBpm("resource/enemy/Enemy1_1.bmp", rend);
    // left
    arr[1] = loadTextureBpm("resource/enemy/Enemy1_4.bmp", rend);
    // up
    arr[2] = loadTextureBpm("resource/enemy/Enemy1_2.bmp", rend);
    // right
    arr[3] = loadTextureBpm("resource/enemy/Enemy1_3.bmp", rend);
    // down attacked
    arr[4] = loadTextureBpm("resource/enemy/Enemy1_5.bmp", rend);
    // left attacked
    arr[5] = loadTextureBpm("resource/enemy/Enemy1_8.bmp", rend);
    // up attacked
    arr[6] = loadTextureBpm("resource/enemy/Enemy1_6.bmp", rend);
    // right attacked
    arr[7] = loadTextureBpm("resource/enemy/Enemy1_7.bmp", rend);
    // DEATH
    arr[8] = loadTextureBpm("resource/enemy/Enemy1_9.bmp", rend);
    // TELEPORT
    arr[9] = loadTextureBpm("resource/enemy/Enemy1_10.bmp", rend);
    return arr;
}
