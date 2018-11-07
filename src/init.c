#include "main.h"

void initializeIO() {

}

void initialize() {

	//initialize the robot
	robot_init();

	/*
	 * Place all robot initilization code here!!!
	 */

	//LCD
	Robot.lcd = lcd_init(uart2);    //setup the robot's lcd
	robot_lcdMenu();                //begin robot start up menu
}
