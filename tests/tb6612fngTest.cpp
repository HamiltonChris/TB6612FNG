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
static bool input1_pin;
static bool input2_pin;
static uint8_t pwm_duty;

static void dummy_gpio(tb6612fng_pin_t pin, bool enable);
static void dummy_pwm(uint8_t duty);

TEST_GROUP(TB6612FNG)
{
    void setup()
    {
        input1_pin = false;
        input2_pin = false;
        standby_pin = false;
        pwm_duty = 0;
        p_tb6612fng = (tb6612fng_t*)malloc(sizeof(tb6612fng_t));
        p_tb6612fng->gpio_set = &dummy_gpio;
        p_tb6612fng->pwm_set = &dummy_pwm;
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

    pwm_duty = 255;
    input1_pin = true;
    input2_pin = true;
    tb6612fng.gpio_set = &dummy_gpio;
    tb6612fng.pwm_set = &dummy_pwm;

    tb6612fng_init(&tb6612fng);

    CHECK(standby_pin);
    CHECK(!input1_pin);
    CHECK(!input2_pin);
    CHECK(tb6612fng.standby_enabled);
    CHECK(STOP == tb6612fng.direction);
    BYTES_EQUAL(0x00, pwm_duty);
    BYTES_EQUAL(0x00, tb6612fng.duty);
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

TEST(TB6612FNG, DirectionStop)
{
    input1_pin = true;
    input2_pin = true;
    tb6612fng_set_direction(p_tb6612fng, STOP);
    CHECK(!input1_pin);
    CHECK(!input2_pin);
    CHECK(STOP == p_tb6612fng->direction);
}

TEST(TB6612FNG, DirectionCW)
{
    input2_pin = true;
    tb6612fng_set_direction(p_tb6612fng, CW_DIRECTION);
    CHECK(input1_pin);
    CHECK(!input2_pin);
    CHECK(CW_DIRECTION == p_tb6612fng->direction);
}

TEST(TB6612FNG, DirectionCCW)
{
    input1_pin = true;
    tb6612fng_set_direction(p_tb6612fng, CCW_DIRECTION);
    CHECK(!input1_pin);
    CHECK(input2_pin);
    CHECK(CCW_DIRECTION == p_tb6612fng->direction);
}

TEST(TB6612FNG, ShortBrake)
{
    pwm_duty = 255;
    tb6612fng_brake(p_tb6612fng);
    BYTES_EQUAL(0x00, pwm_duty);
    BYTES_EQUAL(0x00, p_tb6612fng->duty);
}

TEST(TB6612FNG, MaxSpeed)
{
    tb6612fng_set_speed(p_tb6612fng, 255);
    BYTES_EQUAL(0xFF, pwm_duty);
    BYTES_EQUAL(0xFF, p_tb6612fng->duty);
}

static void dummy_gpio(tb6612fng_pin_t pin, bool enable)
{
    if (STANDBY_PIN == pin)
    {
        standby_pin = enable;
    }
    else if (INPUT1_PIN == pin)
    {
        input1_pin = enable;
    }
    else if (INPUT2_PIN == pin)
    {
        input2_pin = enable;
    }
}

static void dummy_pwm(uint8_t duty)
{
    pwm_duty = duty;
}

/*** end of file ***/
