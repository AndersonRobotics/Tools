#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include <stdint.h>

#pragma pack(push, 1)

struct axis_t{
    float x, y;
};

struct joystick_t{
    uint8_t id;
    struct axis_t a1, a2;

    uint32_t buttons;
};

#pragma pack(pop)

int jstick_getbutton(struct joystick_t js, uint8_t button);

float jstick_getx(struct joystick_t js, int axis);
float jstick_gety(struct joystick_t js, int axis);

#endif