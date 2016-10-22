#include <stdint.h>
#include <stdlib.h>
#include <libgpio.h>
#include "control.h"
#include "motor.h"

unsigned RUNSTEPS = 0;

// Movement registers
unsigned CURRENT_STEP = 0;	// 0 is the top of the rope, RUNSTEPS is the bottom
unsigned TARGET_STEP = 0;

unsigned INITIAL_DELAY = 0;
unsigned CHANGE_DELAY = 0;
enum distance {DIST_ONEQUARTER=1, DIST_HALF, DIST_THREEQUARTER, DIST_FULL} DISTANCE = DIST_FULL;
enum speed {SPEED_SLOW, SPEED_FAST, SPEED_MAX} SPEED = SPEED_FAST;

unsigned UP_PIN = 4;
unsigned DOWN_PIN = 5;
unsigned MODE_PIN = 6;

command_status_t manual_raise() {
	motor_up();
	return COMMAND_FINISHED;
}

command_status_t manual_lower() {
	motor_down();
	return COMMAND_FINISHED;
}

command_status_t learning()
{
	static int in_learning = 0;

	if (0 == in_learning) {
		in_learning = 1;
		RUNSTEPS = 0;
	}

	if (motor_up()) {
		in_learning = 0;
		CURRENT_STEP = 0;
		return COMMAND_FINISHED;
	}

	++RUNSTEPS;
	return COMMAND_INPROGRESS;
}

command_status_t plan() {
	
	INITIAL_DELAY = rand() % 300;
	CHANGE_DELAY = rand() % 30;

	SPEED = rand() % SPEED_MAX;
	DISTANCE = rand() % DIST_FULL + 1;

	return COMMAND_FINISHED;
}

command_status_t runlower()
{
	static int in_runlower = 0;

	if (0 == in_runlower) {
		in_runlower = 1;
		TARGET_STEP = RUNSTEPS;
	}

	if (CURRENT_STEP > RUNSTEPS && motor_canstep()) {
		motor_down();
		return COMMAND_INPROGRESS;
	}

	in_runlower = 0;
	return COMMAND_FINISHED;
}

command_status_t runraise()
{
	static int in_runraise = 0;

	if (0 == in_runraise) {
		in_runraise = 1;
		TARGET_STEP = 0.25 * DISTANCE * RUNSTEPS;
	}

	if (CURRENT_STEP < TARGET_STEP && motor_canstep()) {
		if (motor_up()) {
			goto raisedone;
		}
		return COMMAND_INPROGRESS;
	}

raisedone:
	in_runraise = 0;
	return COMMAND_FINISHED;
}

command_status_t delay(unsigned interval)
{
	static int in_delay = 0;
	static time_t delay_started = 0;

	if (0 == in_initial_delay) {
		in_initial_delay = 1;
		delay_started = time(0);
		return COMMAND_INPROGRESS;
	}

	if (time(0)  < (delay_started + interval)) {
		return COMMAND_INPROGRESS;
	}

	in_delay = 0;
	return COMMAND_FINISHED;
}

command_status_t initial_delay()
{
	return delay(INITIAL_DELAY);
}

command_status_t change_delay()
{
	return delay(CHANGE_DELAY);
}

command_status_t mode_setup()
{
	gpio_value_t up;
	gpio_value_t down;
	gpio_value_t mode = GPIO_VALUE_LOW;

	mode = gpio_pin_get(handle, MODE_PIN);
	while(mode = GPIO_VALUE_LOW) {
		up = gpio_pin_get(handle, UP_PIN);
		down = gpio_pin_get(handle, DOWN_PIN);

		if (GPIO_VALUE_HIGH == up) {
			manual_raise();
		} else if (GPIO_VALUE_HIGH == down) {
			manual_lower();
		}

		mode = gpio_pin_get(handle, MODE_PIN);
	}

	return COMMAND_FINISHED;
}

