#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include "Joystick.h"
#include "settings.h"

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif


typedef enum {
    press_a,
    press_b,
    press_x,
    press_y,
    press_r,
    press_l,
    press_plus,
    press_home,
    hang,
    L_left,
    L_right,
    L_up,
    L_down,
    L_up_right,
    L_up_right_slight,
    L_left_slight,
    L_right_slight,
    L_up_slight,
    L_down_slight
} action_t;

typedef struct {
    action_t action;
    uint8_t duration;
} command_t;

static const command_t wake_up_hang[] = {
    { hang,  50 },
    { press_plus, 5 },
    { hang, 30 }
};

static const command_t release[] = {
    { hang, 1 },
    { press_a, 5 },
    { L_down, 3 },
    { hang, 15 },
    { L_up, 3 },
    { hang, 3 },
    { L_up, 3 },
    { hang, 3 },
    { press_a, 5 },
    { hang, 40 },
    { L_down, 3 },
    { hang, 3 },
    { press_a, 5 },
    { hang, 50 },
    { press_a, 5 },
    { hang, 15 }
};

static const command_t next_box[] = {
    { hang, 1 },
    { L_down, 3 },
    { hang, 3 },
    { L_down, 3 },
    { hang, 3 },
    { L_right, 3 },
    { hang, 3 },
    { L_right, 3 },
    { hang, 3 },
    { press_r, 3 },
    { hang, 5 }
};

#endif