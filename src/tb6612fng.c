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
}

void tb6612fng_enable_standby(tb6612fng_t * p_tb6612fng, bool enable)
{
    p_tb6612fng->gpio_set(STANDBY_PIN, enable);
    p_tb6612fng->standby_enabled = enable;
}

/*** end of file ***/
