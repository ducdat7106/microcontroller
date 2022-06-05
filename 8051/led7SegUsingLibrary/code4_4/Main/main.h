#ifndef _MAIN_H_
#define _MAIN_H_

#include <REGX52.H>
#define FREQ_OSE 12000000 //12MHz

#include "delay.h"
#include "Led7Seg.h"
#include "button.h"
#include "timer0.h"

#define xung_test P3_0

void do_thing_in_interrupt();

#endif
