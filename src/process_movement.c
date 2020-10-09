#include "header.h"

void processMovement(Animated_Entity* entity, Control* keyboard, float* coords, unsigned int* collision, Mix_Chunk* ahSound) {
    if (entity->fight.HP <= 0) {
        entity->mvmnt.ax = 0;
        entity->mvmnt.ax = 0;
        entity->mvmnt.dx = 0;
        entity->mvmnt.dy = 0;
        entity->mvmnt.timePrev = clock();
        return;
    }
    float dt = ((float)(clock() - entity->mvmnt.timePrev)) / 30000;
    entity->mvmnt.timePrev = clock();
    // getting acceleration
    if (keyboard->KEY_W && !keyboard->KEY_D) {
        if (keyboard->KEY_A) {
            entity->mvmnt.ax = -entity->mvmnt.A / sqrt(2);
            entity->mvmnt.ay = -entity->mvmnt.A / sqrt(2);
        } else {
            entity->mvmnt.ay = -entity->mvmnt.A;
            entity->mvmnt.ax = 0;
        }
    } else if (keyboard->KEY_A) {
        if (keyboard->KEY_S) {
            entity->mvmnt.ay = entity->mvmnt.A / sqrt(2);
            entity->mvmnt.ax = -entity->mvmnt.A / sqrt(2);
        } else {
            entity->mvmnt.ax = -entity->mvmnt.A;
            entity->mvmnt.ay = 0;
        }
    } else if (keyboard->KEY_S) {
        if (keyboard->KEY_D) {
            entity->mvmnt.ax = entity->mvmnt.A / sqrt(2);
            entity->mvmnt.ay = entity->mvmnt.A / sqrt(2);
        } else {
            entity->mvmnt.ay = entity->mvmnt.A;
            entity->mvmnt.ax = 0;
        }
    } else if (keyboard->KEY_D) {
        if (keyboard->KEY_W) {
            entity->mvmnt.ay = -entity->mvmnt.A / sqrt(2);
            entity->mvmnt.ax = entity->mvmnt.A / sqrt(2);
        } else {
            entity->mvmnt.ax = entity->mvmnt.A;
            entity->mvmnt.ay = 0;
        }
    } else {
        entity->mvmnt.ax = 0;
        entity->mvmnt.ay = 0;
    }

    // getting max speed
    if (entity->mvmnt.ax == 0) entity->mvmnt.xMS = entity->mvmnt.MS;
    if (entity->mvmnt.ay == 0) entity->mvmnt.yMS = entity->mvmnt.MS;

    if (entity->mvmnt.ax != 0) {
        if (entity->mvmnt.ax > 0)
            entity->mvmnt.xMS = entity->mvmnt.MS * (entity->mvmnt.ax / entity->mvmnt.A);
        else
            entity->mvmnt.xMS = -entity->mvmnt.MS * (entity->mvmnt.ax / entity->mvmnt.A);
    } else {
        entity->mvmnt.xMS = entity->mvmnt.MS;
    }
    if (entity->mvmnt.ay != 0) {
        if (entity->mvmnt.ay > 0)
            entity->mvmnt.yMS = entity->mvmnt.MS * (entity->mvmnt.ay / entity->mvmnt.A);
        else
            entity->mvmnt.yMS = -entity->mvmnt.MS * (entity->mvmnt.ay / entity->mvmnt.A);
    } else {
        entity->mvmnt.yMS = entity->mvmnt.MS;
    }
    // setting distance for next frame movement

    if (entity->mvmnt.ax == 0) {
        entity->mvmnt.dx = closer_to_zero(entity->mvmnt.dx, entity->mvmnt.A * 2 * dt);
    } else if (entity->mvmnt.ax > 0) {
        if (entity->mvmnt.dx + entity->mvmnt.ax * dt > entity->mvmnt.xMS * dt)
            entity->mvmnt.dx = entity->mvmnt.xMS * dt;
        else
            entity->mvmnt.dx = entity->mvmnt.dx + entity->mvmnt.ax * dt;
    } else if (entity->mvmnt.ax < 0) {
        if (entity->mvmnt.dx + entity->mvmnt.ax * dt < -entity->mvmnt.xMS * dt)
            entity->mvmnt.dx = -entity->mvmnt.xMS * dt;
        else
            entity->mvmnt.dx = entity->mvmnt.dx + entity->mvmnt.ax * dt;
    }

    if (entity->mvmnt.ay == 0) {
        entity->mvmnt.dy = closer_to_zero(entity->mvmnt.dy, entity->mvmnt.A * 2 * dt);
    } else if (entity->mvmnt.ay > 0) {
        if (entity->mvmnt.dy + entity->mvmnt.ay * dt > entity->mvmnt.yMS * dt)
            entity->mvmnt.dy = entity->mvmnt.yMS * dt;
        else
            entity->mvmnt.dy = entity->mvmnt.dy + entity->mvmnt.ay * dt;
    } else if (entity->mvmnt.ay < 0) {
        if (entity->mvmnt.dy + entity->mvmnt.ay * dt < -entity->mvmnt.yMS * dt)
            entity->mvmnt.dy = -entity->mvmnt.yMS * dt;
        else
            entity->mvmnt.dy = entity->mvmnt.dy + entity->mvmnt.ay * dt;
    }

    for (int i = -4; i <= 4; i++) {
        for (int j = -3; j <= 3; j++) {
            if (collision[(int)round(coords[0] + i) + (int)round(coords[1] - 1.5 + j) * 500] != 0) {
                entity->mvmnt.x = entity->mvmnt.xPrev;
                entity->mvmnt.y = entity->mvmnt.yPrev;
                entity->mvmnt.dx = 0;
                entity->mvmnt.dy = 0;
                if (!Mix_Playing(1))
                    Mix_PlayChannelTimed(1, ahSound, 0, 1000);
                return;
            }
        }
    }

    // collision[(int)round(coords[0]) + (int)round(coords[1]) * 500]
    entity->mvmnt.xPrev = entity->mvmnt.x;
    entity->mvmnt.yPrev = entity->mvmnt.y;
    entity->mvmnt.x = entity->mvmnt.x + entity->mvmnt.dx;
    entity->mvmnt.y = entity->mvmnt.y + entity->mvmnt.dy;

    // hero is static
    // entity->rect.x = entity->mvmnt.x + entity->mvmnt.dx;
    // entity->rect.y = entity->mvmnt.y + entity->mvmnt.dy;
}
