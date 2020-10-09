#include "header.h"

float abs_f(float num) {
    return num > 0 ? num : -num;
}

float closer_to_zero(float num, float step) {
    if (num > 0) {
        if (num - abs_f(step) < 0) {
            return 0;
        } else {
            return num - abs_f(step);
        }
    } else if (num < 0) {
        if (num + abs_f(step) > 0) {
            return 0;
        } else {
            return num + abs_f(step);
        }
    } else {
        return 0;
    }
}

void getMapCoords(float x, float y, float *arr) {
    float xMap = (x / 55) / METER * 500;
    float yMap = (y / 55) / METER * 500;
    arr[0] = xMap, arr[1] = yMap;
}

void getRealCords(float x, float y, float *arr) {
    arr[0] = x / 500 * 55 * METER;
    arr[1] = y / 500 * 55 * METER;
}

float dCos(float i) {
    i *= (float)M_PI / (float)180;
    return cos(i);
}

int isCloser(Animated_Entity* ent1, Animated_Entity* ent2) {
    float dxy1 = (float)sqrt(pow((double)SCREEN_WIDTH/2 - (double)ent1->rect.x, 2) + 
                             pow((double)SCREEN_HEIGHT/2 - (double)ent1->rect.y, 2));
    float dxy2 = (float)sqrt(pow((double)SCREEN_WIDTH/2 - (double)ent2->rect.x, 2) +
                             pow((double)SCREEN_HEIGHT/2 - (double)ent2->rect.y, 2));
    return dxy1 > dxy2;
}

int isLower(Animated_Entity* ent1, Animated_Entity* ent2) {
    return ent1->rect.y + ent1->rect.h > ent2->rect.y + ent2->rect.h;
}

void swap(void** v1, void** v2) {
    void* buf = *v1;
    *v1 = *v2;
    *v2 = buf;
}

void sortEnt(Animated_Entity** entities, int(*f)(Animated_Entity*, Animated_Entity*)) {
    int size = 0;
    for (; entities[size] != NULL; size++);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if ((*f)(entities[j], entities[j + 1])) {
                swap((void*)&(entities[j]), (void*)&(entities[j + 1]));
            }
        }
    }
}

float distance(Animated_Entity *ent1, Animated_Entity *ent2) {
    return sqrtf(powf(ent1->mvmnt.x - ent2->mvmnt.x, 2) + powf(ent1->mvmnt.y - ent2->mvmnt.y, 2));
}
