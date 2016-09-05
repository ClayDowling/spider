
#ifndef _MOCKPI_H_
#define _MOCKPI_H_

#include <wiringPi.h>

#define UNSET -1

struct pin_setting {
	int pin;
	int value;
};

void init_mocks(void);

int digital_write_count(void);
struct pin_setting digital_write_history(int);

int pin_mode_count(void);
struct pin_setting pin_mode_history(int);

#endif
