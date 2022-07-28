
#define ON 1
#define OFF 0
#define AM 0
#define PM 1

// Timer Configuration...
// adjust these values at will
#define SCREEN	ON	// to display time on PICDEM2+ LCD
#define TICKING OFF	// audible ticking on PICDEM2+
#define PENDULUM ON	// LED pendulum on PICDEM2+
#define	ALARM	ON	// emit audible tone on time match

// Set start time here
#define START_H 8
#define START_M 59
#define START_S 45
#define START_AP AM

#if ALARM == ON
// 9:00.00A = Coffee time
#define ALARM_H 9
#define ALARM_M 00
#define ALARM_AP AM
// Alarm has two tone effect
#define	TONE1	500	// pitch of alarm (highest)-65535(lowest)
#define	TONE2	300
#define ALARM_LENGTH	6	// number of seconds for alarm to sound
#endif

// Sanity check on initial start time
#if START_H > 12 || START_H < 1
#error Invalid hour specification (START_H exceeds range = 1-12)
#endif
#if START_M > 59 || START_M < 0
#error Invalid minute specification (START_M exceeds range = 0-59)
#endif
#if START_S > 59 || START_S < 0
#error Invalid second specification (START_S exceeds range = 0-59)
#endif

