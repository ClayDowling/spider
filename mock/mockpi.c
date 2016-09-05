#include "mockpi.h"

#define MOCK_DEPTH 10

struct pin_setting PIN_HISTORY[MOCK_DEPTH];
int PIN_PTR = 0;

void init_mocks(void)
{
	int i;
	for(i=0; i < MOCK_DEPTH; ++i) {
		PIN_HISTORY[i].pin = UNSET;
		PIN_HISTORY[i].value = UNSET;
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
