#ifndef __DQIOT_CONTROL_H__
#define __DQIOT_CONTROL_H__


#define CONTROL_ADDR 0x60

#define CONTROL_LIGHT 'L';
#define CONTROL_MOTOR 'm';	//电机
#define CONTROL_SOLENOID 'e'; //电磁铁
#define CONTROL_ALARM 'W';

#define CONTROL_OPEN 'o';
#define CONTROL_CLOSED 'c';

#define CONTROL_WAKEUP 'g';

#define CONTROL_SEARCH 'S';

unsigned char control_open_light(void);

unsigned char control_closed_light(void);


unsigned char control_open_motor(void);

unsigned char control_closed_motor(void);


unsigned char control_open_solenoid(void);

unsigned char control_closed_solenoid(void);


unsigned char control_open_alarm(void);

unsigned char control_closed_alarm(void);

void control_test(void);

unsigned char control_get_close_state(void);

unsigned char control_set_close(void);


#endif
