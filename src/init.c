#include "main.h"

void initializeIO() {

}

void initialize() {

	//initialize the robot
	robot_init();
	printf("Initilization in progress...");
	/*
	 * Place all robot initilization code here!!!
	 */

	 //setup individual motors
	 Motor m1 = motor_init(PORT_1, true);
 	Motor m2 = motor_init(PORT_2, true);
 	Motor m3 = motor_init(PORT_3, true);
 	Motor m4 = motor_init(PORT_4, true);

 	Robot.leftDrive = motorSystem_init(2, &m1, &m2);
 	Robot.rightDrive = motorSystem_init(2, &m3, &m4);

	//LCD
	Robot.lcd = lcd_init(uart2);    //setup the robot's lcd
	robot_lcdMenu();                //begin robot start up menu
}
