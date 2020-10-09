#include "header.h"

void processControl(SDL_Event *e, Control *KeyBoard1, Mix_Chunk* walkSound) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            break;
            case SDLK_UP:
            case SDLK_w:
                if (!Mix_Playing(2))
                    Mix_PlayChannelTimed(2, walkSound, 0, 300);
                KeyBoard1->KEY_W = pressed;
                KeyBoard1->KEY_S = unpressed;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if (!Mix_Playing(2))
                    Mix_PlayChannelTimed(2, walkSound, 0, 300);
                KeyBoard1->KEY_A = pressed;
                KeyBoard1->KEY_D = unpressed;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (!Mix_Playing(2))
                    Mix_PlayChannelTimed(2, walkSound, 0, 300);
                KeyBoard1->KEY_S = pressed;
                KeyBoard1->KEY_W = unpressed;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if (!Mix_Playing(2))
                    Mix_PlayChannelTimed(2, walkSound, 0, 300);
                KeyBoard1->KEY_D = pressed;
                KeyBoard1->KEY_A = unpressed;
                break;
            case SDLK_f:
                KeyBoard1->KEY_F = pressed;
            default:
                break;
        }
    }
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                KeyBoard1->KEY_W = unpressed;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                KeyBoard1->KEY_A = unpressed;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                KeyBoard1->KEY_S = unpressed;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                KeyBoard1->KEY_D = unpressed;
                break;
            case SDLK_f:
                KeyBoard1->KEY_F = unpressed;
            default:
                break;
        }
    }
}
