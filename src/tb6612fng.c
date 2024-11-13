/** @file tb6612fng.c
*
* @brief Implementation of the tb6612fng driver module.
*
* @par
*
*/ 

#include "tb6612fng.h"



void tb6612fng_init(tb6612fng_t * p_tb6612fng)
{
    tb6612fng_enable_standby(p_tb6612fng, true);
    tb6612fng_set_direction(p_tb6612fng, STOP);
    tb6612fng_set_speed(p_tb6612fng, 0);
}

void tb6612fng_enable_standby(tb6612fng_t * p_tb6612fng, bool enable)
{
    p_tb6612fng->gpio_set(STANDBY_PIN, enable);
    p_tb6612fng->standby_enabled = enable;
}


void tb6612fng_set_direction(tb6612fng_t * p_tb6612fng, tb6612fng_direction_t direction)
{
    if (STOP == direction)
    {
        p_tb6612fng->gpio_set(INPUT1_PIN, false);
        p_tb6612fng->gpio_set(INPUT2_PIN, false);
    }
    else if (CW_DIRECTION == direction)
    {
        p_tb6612fng->gpio_set(INPUT1_PIN, true);
        p_tb6612fng->gpio_set(INPUT2_PIN, false);
    }
    else if (CCW_DIRECTION == direction)
    {
        p_tb6612fng->gpio_set(INPUT1_PIN, false);
        p_tb6612fng->gpio_set(INPUT2_PIN, true);
    }

    p_tb6612fng->direction = direction;
}

void tb6612fng_set_speed(tb6612fng_t * p_tb6612fng, uint8_t duty)
{
    p_tb6612fng->pwm_set(duty);
    p_tb6612fng->duty = duty;
}

void tb6612fng_brake(tb6612fng_t * p_tb6612fng)
{
    tb6612fng_set_speed(p_tb6612fng, 0);
}

/*** end of file ***/
