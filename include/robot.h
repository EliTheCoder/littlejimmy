/*
 * @file robot.h
 *
 * @brief Collection of files that make up VEX ALL PROSe.
 * Robot data structure and prototypes.
 * Creation of motors to be used by robots.
 * LCD Menus with autonomous selection.
 * This is stricly a BETA release and is not the final version.
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

#ifndef ROBOT_H_
#define ROBOT_H_

#include <NDAPI.h>	//NDA API

//robot modes
#define COMPETITION 0
#define AUTONOMOUS  1
#define RECORD 			2
#define SENSORS 		3

//robot autonomous
#define SKILLS 0
#define AUTON1 1
#define AUTON2 2
#define AUTON3 3
#define AUTON4 4

//robot sensors
#define LIFT 0
#define RIGHT_DRIVE 1
#define LEFT_DRIVE 2
#define TURN  3
#define INTAKE 4

//lift positions
#define LIFT_MAX 2950
#define LIFT_MIN 0
#define LIFT_SCORE 1985

//lift increment
#define LIFT_INCREMENT 20

//intake positions
#define INTAKE_MAX 3000
#define INTAKE_MIN 1000
#define INTAKE_CUBE 1715

//claw increment
#define INTAKE_INCREMENT 100

//controller type
#define DRIVER  1	//the main driver controller
#define PARTNER 2	//the partner driver controller

//robot data structure
struct{
	char mode;					//the current mode of the robot
	char auton;					//the selected autonomous for the match
	LCD lcd;						//the robot's LCD screen
	int liftPos;				//the robot's current target lift position
	double liftConst;		//the robot's lift constant for PID, default is 0.7
	int intakePos;			//the robot's current intake position
	double intakeConst;	//the robot's intake constant for PID. default is 0.7

	//motor systems
	MotorSystem rightDrive;		//robot's right drive
	MotorSystem leftDrive;		//robot's left drive
	MotorSystem intake;				//robot's intake motor system
	MotorSystem lift;					//robot's lift motor system

	//sensors
	Sensor rightDriveSensor; 	//robot's right drive
	Sensor leftDriveSensor;		//robot's left drive sensor
	Sensor liftSensor;				//robot's lift sensor
	Sensor turnSensor;				//robot's turn sensor
	Sensor intakeSensor;			//robot's intake sensor
} Robot;

/* Generic robot functions */

void robot_init();	//initialize the robot

//getter methods
char robot_getAuton();				//retrieve the robot's autonomous for the match
char robot_getMode();					//retrieve the robto's current mode
int robot_getLiftPos();				//retrieve the robot's lift position
int robot_getIntakePos();			//retrieve the robot's intake position
double robot_getLiftConst();	//get the PID lift constant value
double robot_getIntakeConst();//get the PID intake constant value

//lcd methods
void robot_lcdMenu();	//lcd selection menu

//drive methods
void robot_joyDrive(unsigned char controller);													//control robot's drive via the vexNET joystick
void robot_setDrive(char velocity);																			//set both the right and left drives to the same motor velocities
void robot_setDriveSplit(char left, char right);												//set the robot's drive velocities independently
void robot_stop();																											//set the velocity of the drive to zero
void robot_setDriveFor(char velocity, unsigned int time);								//run drive for a certain amount of time at a certain velocity
void robot_setDriveForSplit(char left, char right, unsigned int time);	//run drive for a certain amount of time independently

//lift methods
void robot_liftToPosition(int pos);		//go to the specified position
void robot_setLiftConst(double val);	//set the PID lift constant value

//intake methods
void robot_intakeIn();								//set the robot's intake to in
void robot_intakeOut();								//set the robot's intake to out
void robot_intakeStop();							//stop the robot's intake
void robot_positionIntake(int pos);		//go to position for claw
void robot_setIntakeConst(double val);//set the PID intake constant value

//free memmory
void robot_free();	//free the data associated with robot

#endif /* ROBOT_H_ */
