#include "stm32g030xx.h"

void motor_control(int dir);
void relay_control(int rel);
int hall_feedback(void);
void ice_box_rotation(void);
void valve_config(void);