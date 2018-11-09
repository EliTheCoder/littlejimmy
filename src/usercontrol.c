/*
 * @file usercontrol.c
 *
 * @brief Contains the method for which the client will
 * 		   put in their code to control their robot via
 * 		   the vexNET Joystick.
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

#include "main.h"

/**
 * Insert all joystick commands here and any other functions
 * that will be used to control the robot during the Operator
 * Control Period. This method will be run in a loop with a delay.
 * Therefore there is no need to insert a loop or a delay in this method.
 */
void userControl(){
	robot_joyDrive(DRIVER);
	printf("Running userControl");

	if (joystickGetDigital(DRIVER, 6, JOY_UP)) {
		printf("Detected 6 JOY_UP");
		motorSystem_setVelocity(&Robot.lift, 127);
	} else if(joystickGetDigital(DRIVER, 6, JOY_DOWN)) {
		printf("Detected 6 JOY_DOWN");
		motorSystem_setVelocity(&Robot.lift, -127);
	}
}
