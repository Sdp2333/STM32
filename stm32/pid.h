#ifndef __PID_H
#define __PID_H

short GetSpeed();
	
short PID_Cal(short Speed,short *error);

void SetMotorVoltageAndDirection(int Pwm);





#endif