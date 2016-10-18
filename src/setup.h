/* Defines global constants and variables for the spider
 */

#ifndef _SETUP_H_
#define _SETUP_H_

extern unsigned int RUNSTEPS;
extern unsigned int INITIALDELAY;

enum distance_e {QUARTER, HALF, THREEQUARTERS, FULL};
typedef enum distance_e distance_t;

extern distance_t DISTANCE;

enum speed_e {SLOW, FAST, SPEED_MAX};
typedef enum speed_t speed_t;

extern speed_t SPEED;

#endif
