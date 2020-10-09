#include "header.h"

SDL_Texture* loadTextureBpm(char* image, SDL_Renderer* rend) {
    SDL_Surface* surface = SDL_LoadBMP(image);
    if (!surface) {
        printf("Prosnis ti obosralsa (surface load)\n");
        SDL_DestroyRenderer(rend);
        SDL_Quit();
        exit(-1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Prosnis ti obosralsa(texture)");
        SDL_DestroyRenderer(rend);
        SDL_Quit();
        exit(-1);
    }
    return texture;
}
