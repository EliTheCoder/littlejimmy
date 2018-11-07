/*
 * @file robot.c
 *
 * @brief Implementation of robot methods.
 *        LCD Menus with autonomous selection.
 *        This is strictly a BETA release and is not the final version.
 *
 * Copyright (C) 2016  Jordan M. Kieltyka
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <robot.h>
#include <main.h>

/*
 * Initialize the robot.
 */
void robot_init(){
	Robot.liftConst = 0.7;		//set default value for PID lift constant
}

/*
 * Retrieve the robot's autonomous routine for the
 * match.
 *
 * @return Robot's autonomous routine.
 */
char robot_getAuton(){
	return Robot.auton;
}

/*
 * Retrieve the robot's current mode.
 *
 * @return Robot's current mode.
 */
char robot_getMode(){
	return Robot.mode;
}

/*
 * Retrieve the robot's current lift position.
 *
 * @return The robot's current lift position.
 */
int robot_getLiftPos(){
	return Robot.liftPos;
}

/*
 * Retrieve the robot's current intake position.
 *
 * @return The robot's current intake position.
 */
int robot_getIntakePos(){
	return Robot.intakePos;
}

/*
 * Retrieve the robot's PID lift constant value.
 *
 * @return Robot's PID lift constant value.
 */
double robot_getLiftConst(){
	return Robot.liftConst;
}

/*
 * Retrieve the robot's PID intake constant value.
 *
 * @return Robot's PID intake constant value.
 */
double robot_getIntakeConst(){
	return Robot.intakeConst;
}

/*
 * Display battery voltages.
 * Alliance color selection menu.
 * Starting positions selection menu.
 */
void robot_lcdMenu(){

	lcd_backLight(&Robot.lcd, ON);	//turn on the robot's lcd backlight
	lcd_clear(&Robot.lcd);					//clear lcd

	//splash-screen
	lcd_centerPrint(&Robot.lcd, TOP, "Property of:");					//print lcd
	lcd_centerPrint(&Robot.lcd, BOTTOM, "NDA ROBOTICS");			//print lcd
	delay(1500);																							//delay to make lcd readable
	lcd_clear(&Robot.lcd);																		//clear lcd

	//display low battery warning until battery is replace
	while(powerLevelMain() <= 6000){
		lcd_centerPrint(&Robot.lcd, TOP, "WARNING!!!");						//print lcd warning
		lcd_centerPrint(&Robot.lcd, BOTTOM, "Battery Critical");	//print lcd warning
		lcd_backLight(&Robot.lcd, !lcd_backLightIsOn(Robot.lcd));	//toggle the robot's lcd backlight
		delay(250);																								//delay to make strobe visible
	}

	lcd_backLight(&Robot.lcd, ON);	//turn on the robot's lcd backlight
	lcd_clear(&Robot.lcd);					//clear lcd
	lcd_waitForRelease(Robot.lcd);	//wait for the button to be released before proceeding

	Robot.mode = SENSORS;															//set the default mode to SENSORS

	//select a mode
	while(robot_getMode() == SENSORS){
		Robot.mode = SENSORS;															//set the default mode to SENSORS
		lcd_centerPrint(&Robot.lcd, TOP, "Select Mode");	//print lcd prompt

		//display modes and allow user to select robot mode
		for(int i = 0; !lcd_buttonIsPressed(Robot.lcd, LCD_BTN_CENTER); i = i){

			//Cycle through modes
			if(lcd_buttonIsPressed(Robot.lcd, LCD_BTN_LEFT)){
				i--;
				lcd_waitForRelease(Robot.lcd);
			}
			else if(lcd_buttonIsPressed(Robot.lcd, LCD_BTN_RIGHT)){
				i++;
				lcd_waitForRelease(Robot.lcd);
			}

			//allow selection to wrap around
			if(i > SENSORS)
				i = COMPETITION;
			else if(i < COMPETITION)
				i = SENSORS;

			Robot.mode = i;											//set the current mode for the robot
			lcd_clearLine(&Robot.lcd, BOTTOM);	//clear the bottom LCD line

			//display the current mode choice
			switch(i){
				case COMPETITION:
					lcd_print(&Robot.lcd, BOTTOM, "< COMPETITION  >");
				break;
				case AUTONOMOUS:
					lcd_print(&Robot.lcd, BOTTOM, "<  AUTONOMOUS  >");
				break;
				case RECORD:
					lcd_print(&Robot.lcd, BOTTOM, "<    RECORD    >");
				break;
				case SENSORS:
					lcd_print(&Robot.lcd, BOTTOM, "<   SENSORS    >");
				break;
			}
			delay(10);	//small delay to allow LCD to be readable
		}

		lcd_waitForRelease(Robot.lcd);	//wait for the button to be released before proceeding
		lcd_clear(&Robot.lcd);					//clear the lcd screen

		//cycle through sensors
		for(int i = 0; robot_getMode() == SENSORS && !lcd_buttonIsPressed(Robot.lcd, LCD_BTN_CENTER); i = i){

			lcd_centerPrint(&Robot.lcd, BOTTOM, "<     MENU     >");	//print lcd prompt

			//Cycle through modes
			if(lcd_buttonIsPressed(Robot.lcd, LCD_BTN_LEFT)){
				i--;
				lcd_waitForRelease(Robot.lcd);
			}
			else if(lcd_buttonIsPressed(Robot.lcd, LCD_BTN_RIGHT)){
				i++;
				lcd_waitForRelease(Robot.lcd);
			}

			//allow selection to wrap around
			if(i > TURN)
				i = INTAKE;
			else if(i < LIFT)
				i = INTAKE;

			lcd_clearLine(&Robot.lcd, TOP);	//clear the LCD

			//display the current mode choice
			switch(i){
				case LIFT:
					lcdPrint(Robot.lcd.port, TOP, "Lift: %d", sensor_getValue(Robot.liftSensor));
				break;
				case RIGHT_DRIVE:
					lcdPrint(Robot.lcd.port, TOP, "R. Drive: %d", sensor_getValue(Robot.rightDriveSensor));
				break;
				case LEFT_DRIVE:
					lcdPrint(Robot.lcd.port, TOP, "L. Drive: %d", sensor_getValue(Robot.leftDriveSensor));
				break;
				case TURN:
					lcdPrint(Robot.lcd.port, TOP, "Turn: %d", sensor_getValue(Robot.turnSensor));
				break;
				case INTAKE:
					lcdPrint(Robot.lcd.port, TOP, "Intake: %d", sensor_getValue(Robot.intakeSensor));
				break;
			}
			delay(10);	//small delay to allow LCD to be readable
		}
		lcd_waitForRelease(Robot.lcd);	//wait for the button to be released before proceeding
		lcd_clear(&Robot.lcd);					//clear the lcd screen
	}

	lcd_waitForRelease(Robot.lcd);										//wait for the button to be released before proceeding
	lcd_clear(&Robot.lcd);														//clear the lcd screen
  lcd_centerPrint(&Robot.lcd, TOP, "Select Auton");	//print lcd prompt

	//select the autonomous
	for(int i = 1; !lcd_buttonIsPressed(Robot.lcd, LCD_BTN_CENTER); i = i){

		//Cycle through modes
		if(lcd_buttonIsPressed(Robot.lcd, LCD_BTN_LEFT)){
			i--;
			lcd_waitForRelease(Robot.lcd);
		}
		else if(lcd_buttonIsPressed(Robot.lcd, LCD_BTN_RIGHT)){
			i++;
			lcd_waitForRelease(Robot.lcd);
		}

		//allow selection to wrap around
		if(i > AUTON4)
			i = SKILLS;
		else if(i < SKILLS)
			i = AUTON4;

		Robot.auton = i;										//set the current mode for the robot
		lcd_clearLine(&Robot.lcd, BOTTOM);	//clear the bottom LCD line

		//display the current mode choice
		switch(i){
			case SKILLS:
				lcd_print(&Robot.lcd, BOTTOM, "<    SKILLS    >");
			break;
			case AUTON1:
				lcd_print(&Robot.lcd, BOTTOM, "< AUTONOMOUS 1 >");
			break;
			case AUTON2:
				lcd_print(&Robot.lcd, BOTTOM, "< AUTONOMOUS 2 >");
			break;
			case AUTON3:
				lcd_print(&Robot.lcd, BOTTOM, "< AUTONOMOUS 3 >");
			break;
			case AUTON4:
				lcd_print(&Robot.lcd, BOTTOM, "< AUTONOMOUS 4 >");
			break;
		}
		delay(10);	//small delay to allow LCD to be readable
	}
	lcd_waitForRelease(Robot.lcd);	//wait for the button to be released before proceeding
	lcd_clear(&Robot.lcd);					//clear the lcd screen
}

/*
 *	Control robot's drive via the vexNET joystick
 *
 *	@param controller The joystick that will be controlling the drive.
 */
void robot_joyDrive(unsigned char controller){

	//used for dead zoning joystick
	if(abs(joystickGetAnalog(controller, 2)) > 10)
		motorSystem_setVelocity(&Robot.rightDrive, joystickGetAnalog(controller, 2));	//set robot's right drive velocity
	else
		motorSystem_stop(&Robot.rightDrive);	//stop robot's right drive

	//used for dead zoning joystick
	if(abs(joystickGetAnalog(controller, 3)) > 10)
		motorSystem_setVelocity(&Robot.leftDrive, joystickGetAnalog(controller, 3));	//set robot's left drive velocity
	else
		motorSystem_stop(&Robot.leftDrive);	//stop robot's left drive
}

/*
 *	Set both of the robot's drives to the desired
 *	velocity.
 *
 *	@param velocity The desired velocity for the left and right drive.
 */
void robot_setDrive(char velocity){
	robot_setDriveSplit(velocity, velocity);	//set the right and left drive to the desired velocity
}

/*
 * Set the desired velocity for the left and right drive.
 *
 * @param left The desired velocity for the left drive.
 * @param right The desired velocity for the right drive.
 */
void robot_setDriveSplit(char left, char right){
	motorSystem_setVelocity(&Robot.leftDrive, left);		//set the left drive velocity
	motorSystem_setVelocity(&Robot.rightDrive, right);	//set the right drive velocity
}

/*
 * Set the robot's drive train velocities to zero.
 */
void robot_stop(){
	robot_setDrive(0);	//set both right and left drive to zero
}

/*
 * Set the robot's drives for a desired amount of time then stop.
 *
 * @param velocity The desired drive velocity.
 * @param time The amount of time in ms for the drive to run.
 */
void robot_setDriveFor(char velocity, unsigned int time){
	robot_setDriveForSplit(velocity, velocity, time);
}

/*
 * Set the robot's drives independently for a desired amount of time
 * then stop.
 *
 * @param left The desired velocity of the left drive.
 * @param right The desired velocity of the right drive.
 * @param time The amount of time in ms for the drives to run.
 */
void robot_setDriveForSplit(char left, char right, unsigned int time){
	robot_setDriveSplit(left, right);	//set the right and left drive to the desired velocities
	delay(time);											//pause for the desired amount of time
	robot_stop();											//stop the drive
}

/*
 * Have the robot's lift go to the desired position
 *
 * @param pos The desired lift position.
 */
 void robot_liftToPosition(int pos){

 	//it is the autonomous period
 	if(isAutonomous())
 		motorSystem_setTillPID(&Robot.lift, &Robot.liftSensor, robot_getLiftConst(), pos);

 	//it is op control period
 	else{
 		//update motor in PID loop until sensor target value is near
 		if(sensor_getValue(Robot.liftSensor) != pos || (pos - sensor_getValue(Robot.liftSensor)) * robot_getLiftConst() < 10)
 			motorSystem_setVelocity(&Robot.lift, (pos - sensor_getValue(Robot.liftSensor)) * robot_getLiftConst());

 		//target position has been reached
 		else
 			motorSystem_stop(&Robot.lift);	//stop motor
 	}
}

/**
 * Set the PID lift constant value for the
 * desired lift behavior.
 *
 * @param val The new value for the lift constant.
 */
void robot_setLiftConst(double val){
	Robot.liftConst = val;
}

/*
 * Set the robot's intake to the on state.
 */
void robot_intakeIn(){
	motorSystem_setVelocity(&Robot.intake, 127);
}

/*
 * Set the robot's intake to the out state.
 */
void robot_intakeOut(){
	motorSystem_setVelocity(&Robot.intake, -127);
}

/*
 * Turn off the robot's intake.
 */
void robot_intakeStop(){
	motorSystem_stop(&Robot.intake);
}

/*
 * Have the robot's lift go to the desired position
 *
 * @param pos The desired lift position.
 */
 void robot_positionIntake(int pos){

 	//it is the autonomous period
 	if(isAutonomous())
 		motorSystem_setTillPID(&Robot.intake, &Robot.intakeSensor, robot_getIntakeConst(), pos);

 	//it is op control period
 	else{
 		//update motor in PID loop until sensor target value is near
 		if(sensor_getValue(Robot.intakeSensor) != pos || (pos - sensor_getValue(Robot.intakeSensor)) * robot_getIntakeConst() < 10)
 			motorSystem_setVelocity(&Robot.intake, (pos - sensor_getValue(Robot.intakeSensor)) * robot_getIntakeConst());

 		//target position has been reached
 		else
 			motorSystem_stop(&Robot.intake);	//stop motor
 	}
}

/**
 * Set the PID intake constant value for the
 * desired intake behavior.
 *
 * @param val The new value for the lift constant.
 */
void robot_setIntakeConst(double val){
	Robot.intakeConst = val;
}

/*
 * Free all sensors, sensor systems and motor systems that are associated
 * with the robot.
 */
void robot_free(){

	//free motor systems
	motorSystem_free(&Robot.rightDrive);	//free the right drive
	motorSystem_free(&Robot.leftDrive);		//free the left drive
	motorSystem_free(&Robot.intake);			//free the intake
	motorSystem_free(&Robot.lift);				//free the lift

	//free sensors
	sensor_free(&Robot.rightDriveSensor);	//free the right drive sensor
	sensor_free(&Robot.leftDriveSensor);	//free the left drive sensor
	sensor_free(&Robot.liftSensor);				//free the lift sensor
	sensor_free(&Robot.intakeSensor);			//free the intake sensor
	sensor_free(&Robot.turnSensor);				//free the turn sensor
}
