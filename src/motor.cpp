#include <libgpio.h>
#include <stdlib.h>
#include "motor.h"
#include "setup.h"

int initialized = 0;

unsigned LIMIT_PIN = 7;
unsigned STEP_PIN = 8;
unsigned DIR_PIN = 9;

gpio_handle_t handle = 0;

void step_motor(void);
void initialize(void);

void initialize()
{
	if (!initialized) {
		handle = gpio_open(0);
		if (handle == GPIO_HANDLE_INVALID) {
			err(EXIT_FAILURE, "gpio_open failed");
		}
		gpio_pin_input(handle, LIMIT_PIN);
		// Without a pulldow resistor on the circuit the pin
		// will flicker on and off randomly.
		gpio_pin_pulldown(handle, LIMIT_PIN);
		gpio_pin_output(handle, STEP_PIN);
		gpio_pin_output(handle, LIMIT_PIN);

		initialized = 1;
	}
}

int motor_up()
{
	initialize();
	if (gpio_pin_get(handle, LIMIT_PIN) == GPIO_VALUE_LOW) {
		step_motor();
		return 0;
	}
	return 1;
}

int motor_down()
{
	initialize();
	step_motor();
	return 0;
}

void step_motor()
{
	gpio_pin_set(handle, STEP_PIN, GPIO_PIN_HIGH);
	gpio_pin_set(handle, STEP_PIN, GPIO_PIN_LOW);
}
