#include "header.h"

int get_direction(Animated_Entity *aEntity) {
    int direction = 270;
    float dx = aEntity->mvmnt.dx;
    float dy = aEntity->mvmnt.dy;
    float dxy = sqrtf(dx * dx + dy * dy);
    if (closer_to_zero(dx, 3) == 0 && closer_to_zero(dy, 3) == 0) {
        direction = 270;
    } else if (dx == 0 && dy >= 0) {
        direction = 90;
    } else if (dx == 0 && dy < 0) {
        direction = 270;
    } else if (dy == 0 && dx > 0) {
        direction = 0;
    } else if (dy == 0 && dx < 0) {
        direction = 180;
    } else {
        if (dx / dxy > dCos(0.125 * 180)) {
            direction = 0;
        } else if (dx / dxy > dCos(0.375 * 180)) {
            if (dy > 0) direction = 45;
            if (dy < 0) direction = 315;
        } else if (dx / dxy > dCos(0.625 * 180)) {
            if (dy > 0) direction = 90;
            if (dy < 0) direction = 270;
        } else if (dx / dxy > dCos(0.875 * 180)) {
            if (dy > 0) direction = 135;
            if (dy < 0) direction = 225;
        } else {
            if (dy != 0) direction = 180;
        }
    }
    return direction;
}
