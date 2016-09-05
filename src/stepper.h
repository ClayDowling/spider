#ifndef _STEPPER_H_
#define _STEPPER_H_

struct stepper;

struct stepper *stepper_create(int pinA, int pinB, int pinC, int pinD);
void stepper_destroy(struct stepper*);

void stepper_step(struct stepper*, int steps, int delay);

#endif
