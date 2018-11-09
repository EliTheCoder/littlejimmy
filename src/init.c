#include "main.h"

void initializeIO() {

}

void initialize() {

	//initialize the robot
	robot_init();

	/*
	 * Place all robot initilization code here!!!
	 */

	 //setup individual motors
	 Motor leftMotor1 = motor_init(PORT_1, false);
	 Motor leftMotor2 = motor_init(PORT_2, false);
	 Motor rightMotor1 = motor_init(PORT_3, false);
	 Motor rightMotor2 = motor_init(PORT_4, false);
	 Motor intakeMotor1 = motor_init(PORT_5, false);
	 Motor conveyorMotor1 = motor_init(PORT_6, false);
	 Motor flywheelMotor1 = motor_init(PORT_7, false);
	 Motor flywheelMotor2 = motor_init(PORT_8, false);
	 Motor liftMotor1 = motor_init(PORT_9, false);
	 Motor liftMotor2 = motor_init(PORT_10, false);

	 //setup default motor systems
	 Robot.leftDrive = motorSystem_init(2, &leftMotor1, &leftMotor2);
	 Robot.rightDrive = motorSystem_init(2, &rightMotor1, &rightMotor2);
	 Robot.intake = motorSystem_init(4, &intakeMotor1, &conveyorMotor1, &flywheelMotor1, &flywheelMotor2);
	 Robot.lift = motorSystem_init(2, &liftMotor1, &liftMotor2);

	//LCD
	Robot.lcd = lcd_init(uart2);    //setup the robot's lcd
	robot_lcdMenu();                //begin robot start up menu
}
