#include "mockpi.h"

#define MOCK_DEPTH 20

struct pin_setting PIN_HISTORY[MOCK_DEPTH];
int PIN_PTR = 0;

struct pin_setting MODE_HISTORY[MOCK_DEPTH];
int MODE_PTR = 0;

void init_mocks(void)
{
	int i;
	for(i=0; i < MOCK_DEPTH; ++i) {
		PIN_HISTORY[i].pin = UNSET;
		PIN_HISTORY[i].value = UNSET;
	}

	for(i=0; i < MOCK_DEPTH; ++i) {
		MODE_HISTORY[i].pin = UNSET;
		MODE_HISTORY[i].value = UNSET;
	}
}

void digitalWrite(int pin, int value)
{
	PIN_HISTORY[PIN_PTR].pin = pin;
	PIN_HISTORY[PIN_PTR].value = value;
	++PIN_PTR;
}

int digital_write_count()
{
	return PIN_PTR;
}

struct pin_setting digital_write_history(int ptr)
{
	struct pin_setting empty = { .pin=UNSET, .value=UNSET };
	if (ptr < PIN_PTR) {
		return PIN_HISTORY[ptr];
	}
	return empty;
}

void pinMode(int pin, int mode)
{
	MODE_HISTORY[MODE_PTR].pin = pin;
	MODE_HISTORY[MODE_PTR].value = mode;
	++MODE_PTR;
}

int pin_mode_count()
{
	return MODE_PTR;
}

struct pin_setting pin_mode_history(int ptr)
{
	struct pin_setting empty = { .pin=UNSET, .value=UNSET };
	if (ptr < MODE_PTR) {
		return MODE_HISTORY[ptr];
	}
	return empty;
}
