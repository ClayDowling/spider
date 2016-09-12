#include <stdlib.h>
#include <wiringPi.h>
#include "stepper.h"

struct stepper {
	int position;

	int pinA;
	int pinB;
	int pinC;
	int pinD;
};

struct stepper* stepper_create(int pinA, int pinB, int pinC, int pinD)
{
	struct stepper *s = calloc(1, sizeof(struct stepper));

	s->pinA = pinA;
	s->pinB = pinB;
	s->pinC = pinC;
	s->pinD = pinD;

	pinMode(s->pinA, OUTPUT);
	pinMode(s->pinB, OUTPUT);
	pinMode(s->pinC, OUTPUT);
	pinMode(s->pinD, OUTPUT);

	return s;
}

void stepper_destroy(struct stepper *s)
{
	free(s);
}

void stepper_step(struct stepper *s, int steps, int delay)
{
	digitalWrite(s->pinA, HIGH);
	digitalWrite(s->pinC, HIGH);
}
