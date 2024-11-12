/** @file tb6612fngTest.cpp
*
* @brief Unit tests for the tb6612fng driver module.
*
* @par
*
*/ 

extern "C"
{
#include "tb6612fng.h"
}

#include "CppUTest/TestHarness.h"

static tb6612fng_t * p_tb6612fng;
static bool standby_pin;

static void dummy_gpio(tb6612fng_pin_t pin, bool enable);

TEST_GROUP(TB6612FNG)
{
    void setup()
    {
        standby_pin = false;
        p_tb6612fng = (tb6612fng_t*)malloc(sizeof(tb6612fng_t));
        p_tb6612fng->gpio_set = &dummy_gpio;
        tb6612fng_init(p_tb6612fng);
    }

    void teardown()
    {
        free(p_tb6612fng);
    }
};

TEST(TB6612FNG, Init)
{
    tb6612fng_t tb6612fng;
    tb6612fng.gpio_set = &dummy_gpio;
    tb6612fng_init(&tb6612fng);
    CHECK(standby_pin);
    CHECK(tb6612fng.standby_enabled);
}

TEST(TB6612FNG, StandbyEnable)
{
    standby_pin = false;
    tb6612fng_enable_standby(p_tb6612fng, true);
    CHECK(standby_pin);
    CHECK(p_tb6612fng->standby_enabled);
}

TEST(TB6612FNG, StandbyDisable)
{
    tb6612fng_enable_standby(p_tb6612fng, false);
    CHECK(!standby_pin);
    CHECK(!p_tb6612fng->standby_enabled);
}

static void dummy_gpio(tb6612fng_pin_t pin, bool enable)
{
    if (STANDBY_PIN == pin)
    {
        standby_pin = enable;
    }
}

/*** end of file ***/
