/*
 * @file rr_auto.h
 *
 * @brief Allows VEX ROBOTICS COMPETITION (TM) teams to record values from
 * 		  motor ports and digital ports and save them to a file on the
 * 		  CORTEX. Files then can be played back during the autonomous
 * 		  portion of the VEX ROBOTICS COMPETITION (TM).
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

#ifndef RR_AUTO_H_
#define RR_AUTO_H_

#include <string.h>
#include <API.h>
#include <NDAPI.h>

//main methods
void robot_record(const char* name, unsigned long int time);	//record the value of the motor ports for 15 seconds
void robot_replay(const char* name);							//play-back the value of all motor ports

//helper methods
void writeMotorValue(FILE* file, int port);			//write a motor value to a file
int readMotorValue(FILE* file);						//read a motor value from a file
void writeDigitalPortValue(FILE* file, int port);	//write a digital port value to a file
int readDigitalPortValue(FILE* file);				//read a digital port value to a file
int ctoi(char c);									//convert a character into its int value
char itoc(int i);									//convert an int to its character value

#endif /* RR_AUTO_H_ */
