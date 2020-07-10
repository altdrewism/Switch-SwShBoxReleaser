#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include "Joystick.h"
#include "settings.h"
#include "egg_cycles.h"

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
    { hang,  50 }
};

static const command_t fly_to_breading_steps[] = {
    { press_a, 5 },
    { hang, 50 },
    { press_x, 7},
    { hang, 35 },
    { press_plus, 5 },
    { hang, 90 },
    { L_up_right_slight, 2 },
    { hang, 5 },
    { press_a, 5 },
    { hang, 25 },
    { press_a, 5 },
    { hang, 90 }
};

static const command_t go_in_out_nursery[] = {
    { L_up_slight, 5 },
    { hang, 5 },
    { L_up, 20 },
    { hang, 100 },
    { L_down, 15 },
    { hang, 80 },
    { press_plus, 5 },
    { hang, 10 }
};

static const command_t go_to_circle1[] = {
    { L_left_slight, 5 },
    { hang, 5 },
    { L_left, 28 },
    { hang, 20 }
};

static const command_t go_to_circle2[] = {
    { L_left_slight, 5 },
    { hang, 5 },
    { L_left, 13 },
    { hang, 20 }
};

static const command_t go_to_circle3[] = {
    { L_down_slight, 7 },
    { hang, 5 },
    { L_down, 7 },
    { hang, 15 },
    { L_left_slight, 5 },
    { hang, 5 },
    { L_left, 45 },
    { hang, 15 },
    { L_right_slight, 5},
    { hang, 5 }
};

static const command_t approach[] = {
    { hang, 20 },
    { L_right_slight, 5 },
    { hang, 10 },
    { L_up_right, 70 },
    { hang, 5 },
};

static const command_t speak[] = {
    { press_a, 5 },
    { hang, 30 },
    { press_a, 5 },
    { hang, 30 },
    { L_down, 5 },
    { hang, 5 },
    { L_down, 5},
    { hang, 10 },
    { press_a, 5 },
    { hang, 140 },
    { press_b, 5 },
    { hang, 75 },
    { press_b, 5 },
    { hang, 60 },
    { press_b, 5 },
    { hang, 20 }
};

static const command_t open_box[] = {
    { hang, 40 },
    { press_x, 5},
    { hang, 35 },
    { press_a, 5 },
    { hang, 60 },
    { press_r, 5 },
    { hang, 75 },
    { press_y, 3 },
    { hang, 3 },
    { press_y, 3 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t select_col[] = {
    { press_a, 3 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 3 },
    { press_a, 3 },
    { hang, 10 }
};

static const command_t close_box[] = {
    { press_a, 3 },
    { hang, 3 },
    { press_b, 3 },
    { hang, 75 },
    { press_b, 3 },
    { hang, 60 },
    { press_x, 3 },
    { hang, 35 } 
};

static const command_t grab_eggs1_pre[] = {
    { L_left, 1 },
    { hang, 3 },
    { L_up, 1 },
    { hang, 5 },
    { press_l, 5 },
    { hang, 10 },
    { press_a, 1 },
    { hang, 5 },
    { press_r, 5 },
    { hang, 10 },
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 1 }
};

static const command_t grab_eggs1_post[] = {
    { L_left, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t grab_eggs2_pre[] = {
    { L_right, 1 },
    { hang, 3 },
    { L_up, 3 },
    { hang, 3 },
    { press_a, 3 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 1 }
};

static const command_t grab_eggs2_post[] = {
    { L_left, 1 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t grab_eggs3_pre[] = {
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 3 },
    { L_up, 3 },
    { hang, 3 },
    { press_a, 3 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 1 }
};

static const command_t grab_eggs3_post[] = {
    { L_left, 1 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t grab_eggs4_pre[] = {
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 3 },
    { L_up, 1 },
    { hang, 3 },
    { press_a, 3 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 1 }
};

static const command_t grab_eggs4_post[] = {
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t grab_eggs5_pre[] = {
    { L_left, 1 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_up, 1 },
    { hang, 3 },
    { press_a, 3 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 1 }
};

static const command_t grab_eggs5_post[] = {
    { L_right, 1 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t grab_eggs6_pre[] = {
    { L_left, 1 },
    { hang, 3 },
    { L_left, 1 },
    { hang, 3 },
    { L_up, 1 },
    { hang, 3 },
    { press_a, 3 },
    { hang, 3 },
    { L_right, 1 },
    { hang, 1 }
};

static const command_t grab_eggs6_post[] = {
    { press_r, 5 },
    { hang, 5 },
    { L_right, 1 },
    { hang, 3 },
    { L_down, 1 },
    { hang, 1 }
};

static const command_t save_game[] = {
    { hang, 40 },
    { press_x, 5},
    { hang, 35 },
    { press_r, 5 },
    { hang, 75 },
    { press_a, 3 },
    { hang, 100 }
};

static const command_t sleep[] = {
    { press_home, 25 },
    { hang, 5 },
    { press_a, 5 }
};

#endif