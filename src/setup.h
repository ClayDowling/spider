/* Defines global constants and variables for the spider
 */

#ifndef _SETUP_H_
#define _SETUP_H_

#include <stdint.h>
#include <libgpio.h>

enum distance_e {QUARTER, HALF, THREEQUARTERS, FULL};
typedef enum distance_e distance_t;

enum speed_e {SLOW, FAST, SPEED_MAX};
typedef enum speed_t speed_t;

gpio_handle_t HANDLE;

#endif
