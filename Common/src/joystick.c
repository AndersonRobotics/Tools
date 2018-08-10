#include "joystick.h"

int jstick_getbutton(struct joystick_t js, unsigned uint8_t button){
    if(button > 32){
        return 0;
    }

    return (js.buttons & (1 << button)) == (1 << button);
}

float jstick_getx(struct joystick_t js, int axis){
    switch(axis){
        case 1:
        return js.a1.x;

        case 2:
        return js.a2.x;

        case 3:
        return js.a3.x;

        default:
        return -1;
    }
}

float jstick_gety(struct joystick_t js, int axis){
    switch(axis){
        case 1:
        return js.a1.y;

        case 2:
        return js.a2.y;

        case 3:
        return js.a3.y;

        default:
        return -1;
    }
}