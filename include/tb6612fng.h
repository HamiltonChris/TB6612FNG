/** @file tb6612fng.h
*
* @brief Implementation of the tb6612fng driver module.
*
* @par
*
*/

#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <stdint.h>
#include <stdbool.h>

typedef enum tb6612fng_pin_e
{
    INPUT1_PIN  = 0,
    INPUT2_PIN,
    STANDBY_PIN,
} tb6612fng_pin_t;

typedef enum tb6612fng_direction_e
{
    STOP = 0,
    CW_DIRECTION,
    CCW_DIRECTION,
} tb6612fng_direction_t;

typedef struct tb6612fng_s {
    bool standby_enabled;
    tb6612fng_direction_t direction;
    uint8_t duty;
    void (*gpio_set)(tb6612fng_pin_t, bool);
    void (*pwm_set)(uint8_t duty);
} tb6612fng_t;

void tb6612fng_init(tb6612fng_t * p_tb6612fng);
void tb6612fng_enable_standby(tb6612fng_t * p_tb6612fng, bool enable);
void tb6612fng_set_direction(tb6612fng_t * p_tb6612fng, tb6612fng_direction_t direction);
void tb6612fng_set_speed(tb6612fng_t * p_tb6612fng, uint8_t duty);
void tb6612fng_brake(tb6612fng_t * p_tb6612fng);

#endif // TB6612FNG_H

/*** end of file ***/
