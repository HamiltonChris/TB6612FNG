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
    INPUT2_PIN  = 1,
    STANDBY_PIN = 2,
} tb6612fng_pin_t;

typedef struct tb6612fng_s {
    bool standby_enabled;
    void (*gpio_set)(tb6612fng_pin_t, bool);
} tb6612fng_t;

void tb6612fng_init(tb6612fng_t * p_tb6612fng);
void tb6612fng_enable_standby(tb6612fng_t * p_tb6612fng, bool enable);

#endif // TB6612FNG_H

/*** end of file ***/
