/* Handle system controls.
 */

#ifndef _CONTROL_H_
#define _CONTROL_H_

// Main control loop
void operate();

/* Implementations of commands.  These return COMMAND_FINISHED if they were
 * able to complete their commands, and COMMAND_INPROGRESS if they need to
 * be run again.
 */

enum command_status {
	COMMAND_INPROGRESS,	// Do not advance state machine.  Operation 
				// needs more cycles to complete.
	COMMAND_FINISHED,	// Advance state machine, operation complete.
	COMMAND_MAX};		// TERMINAL

typedef enum command_status command_status_t;

command_status_t manual_raise();
command_status_t manual_lower();
command_status_t learning();
command_status_t plan();
command_status_t runlower();
command_status_t runraise();
command_status_t initial_delay();
command_status_t change_delay();

command_status_t mode_setup();
command_status_t mode_run();`

#endif
