#include "main.h"

void autonomous() {
	lcd_centerPrint(&Robot.lcd, TOP, "Autonomous Mode");	//print to lcd
	lcd_centerPrint(&Robot.lcd, BOTTOM, "ACTIVE");			//print to lcd

	//play the autonomous that was selected
	switch(robot_getAuton()){
		case SKILLS:
			robot_replay("sk.txt");
		break;
		case AUTON1:
			robot_replay("a1.txt");
		break;
		case AUTON2:
			robot_replay("a2.txt");
		break;
		case AUTON3:
			robot_replay("a3.txt");
		break;
		case AUTON4:
			robot_replay("a4.txt");
		break;
	}
}
