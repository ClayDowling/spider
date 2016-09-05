#include <stdlib.h>
#include <wiringPi.h>
#include "stepper.h"

struct stepper {
	int position;
};

struct stepper* stepper_create(int pinA, int pinB, int pinC, int pinD)
{
	struct stepper *s = calloc(1, sizeof(struct stepper));

	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	pinMode(pinC, OUTPUT);
	pinMode(pinD, OUTPUT);

	return s;
}

void stepper_destroy(struct stepper *s)
{
	free(s);
}

