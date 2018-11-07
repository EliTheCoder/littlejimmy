#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	lcd_centerPrint(&Robot.lcd, TOP, "Driver");				//print to lcd
	lcd_centerPrint(&Robot.lcd, BOTTOM, "Control Mode");	//print to lcd

	//continue to loop until competition is ended
	while(robot_getMode() == COMPETITION){
		userControl();
		delay(20);
	}

	//test the autonomous selected
	if(robot_getMode() == AUTONOMOUS)
		autonomous();

	//record the autonomous selected
	if(robot_getMode() == RECORD)
		switch(robot_getAuton()){
			case SKILLS:
				robot_record("sk.txt", 60000);
			break;
			case AUTON1:
				robot_record("a1.txt", 15000);
			break;
			case AUTON2:
				robot_record("a2.txt", 15000);
			break;
			case AUTON3:
				robot_record("a3.txt", 15000);
			break;
			case AUTON4:
				robot_record("a4.txt", 15000);
			break;
	}

	lcd_centerPrint(&Robot.lcd, TOP, "Rebooting");	//print to lcd
	lcd_centerPrint(&Robot.lcd, BOTTOM, "System");	//print to lcd
	delay(1000);																		//delay to read LCD message
	robot_free();																		//free memmory from the robot
	exit(EXIT_SUCCESS);															//restart program with exit code EXIT_SUCCESS
}
