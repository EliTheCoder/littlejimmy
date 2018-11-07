/*
 * @file NDAPI.h
 *
 * @brief Contains the Motor, MotorSystem, Sensor, SensorSystem, and LCD
 *		  data structure as well as the prototypes methods to be used with
 *		  these data structures. This API is meant to make programming more
 *		  organized and more logical for middle school level, high school
 *		  level and university level teams participating the VEX ROBOTICS
 *		  COMPETITION (TM).
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

#ifndef NDAPI_H_
#define NDAPI_H_

#include <string.h>
#include <API.h>

// ------------------------------------------ Ports --------------------------------------------

//motor ports
#define PORT_1  1	//motor port one
#define PORT_2  2	//motor port two
#define PORT_3  3	//motor port three
#define PORT_4  4	//motor port four
#define PORT_5  5	//motor port five
#define PORT_6  6	//motor port six
#define PORT_7  7	//motor port seven
#define PORT_8  8	//motor port eight
#define PORT_9  9	//motor port nine
#define PORT_10 10	//motor port ten

//I2C IME ports
#define I2C_1  0	//I2C sensor port one
#define I2C_2  1	//I2C sensor port two
#define I2C_3  2	//I2C sensor port three
#define I2C_4  3	//I2C sensor port four
#define I2C_5  4	//I2C sensor port five
#define I2C_6  5	//I2C sensor port six
#define I2C_7  6	//I2C sensor port seven
#define I2C_8  7	//I2C sensor port eight
#define I2C_9  8	//I2C sensor port nine
#define I2C_10 9	//I2C sensor port ten

//analog sensor ports
#define IN_1 1	//analog sensor port one
#define IN_2 2	//analog sensor port two
#define IN_3 3	//analog sensor port three
#define IN_4 4	//analog sensor port four
#define IN_5 5	//analog sensor port five
#define IN_6 6	//analog sensor port six
#define IN_7 7	//analog sensor port seven
#define IN_8 8	//analog sensor port eight

//digital sensor ports
#define DGTL_1  1		//digital sensor port one
#define DGTL_2  2		//digital sensor port two
#define DGTL_3  3		//digital sensor port three
#define DGTL_4  4		//digital sensor port four
#define DGTL_5  5		//digital sensor port five
#define DGTL_6  6		//digital sensor port six
#define DGTL_7  7		//digital sensor port seven
#define DGTL_8  8		//digital sensor port eight
#define DGTL_9  9		//digital sensor port nine
#define DGTL_10 10	//digital sensor port ten
#define DGTL_11 11	//digital sensor port eleven
#define DGTL_12 12	//digital sensor port twelve

//------------------------------------- Data Structures ----------------------------------------

//motor data structure
struct{
	int port;				//the port the motor is assigned to
	int velocity;		//the current velocity of the motor
	bool reversed;	//flag for if the motor is reversed or not
} typedef Motor;

//motor system data structure
struct{
	Motor* motors;			//motors that are part of the system
	int size;						//number of motors part of the motor system
	int velocity;				//the current velocity of the motor system
} typedef MotorSystem;

//sensor data structure
struct{
	void* sensor;		//preset sensor
	int type;				//the type of sensor
	int* ports;			//the ports the sensor is connected to
	int size;				//the number of ports the sensor uses
	bool opposite;	//flag for returning opposite values
	bool analog;		//a flag to determine if the sensor is digital or analog
} typedef Sensor;

//sensor system data structure
struct{
	Sensor* sensors;			//sensors that are part of the system
	int size;							//the amount of sensors in the system
} typedef SensorSystem;

//lcd data structure
struct{
	FILE* port;			//the port that the lcd is using
	char line1[16];	//the string of characters on the first line of the lcd
	char line2[16];	//the string of characters on the second line of the lcd
	bool backLight;	//the state of the lcd back light
}typedef LCD;

// ---------------------------------------- Motor ----------------------------------------------

Motor motor_init(int port, bool isReversed);														//set the port for the motor
bool motor_reverse(Motor* target);																			//reverse the motor
void motor_setVelocity(Motor* target, int velocity);										//set the velocity of the motor
int motor_getPort(Motor target);																				//retrieve the port of the motor
int motor_getVelocity(Motor target);																		//retrieve the velocity of the motor
bool motor_isReversed(Motor target);																		//retrieve the reversed flag of the motor
void motor_stop(Motor* target);																					//set the velocity of the motor to zero
void motor_setFor(Motor* target, int velocity, unsigned int time);			//run motor for a certain amount of time
void motor_setTill(Motor* target, Sensor* obs, int velocity, int val);	//run motor until a target sensor value has been reached
void motor_setTillPID(Motor* target, Sensor* obs, double k, int val);		//run motor until a target sensor value has been reached with PID

// ------------------------------------ Motor System -------------------------------------------

bool motorSystem_contains(MotorSystem target, Motor m);															//check to see if the motor system contains the motor
MotorSystem motorSystem_init(const int motors, Motor* m, ...);											//assign the motors to the motor system
void motorSystem_setVelocity(MotorSystem* target, int velocity);										//set the velocity of the motor system
int motorSystem_getVelocity(MotorSystem target);																		//retrieve the velocity of the motor system
int motorSystem_getSize(MotorSystem target);																				//retrieve the size of the motor system
void motorSystem_stop(MotorSystem* target);																					//set the velocity of the motor system to zero
void motorSystem_setFor(MotorSystem* target, int velocity, unsigned int time);			//run the motor system for a desired amount of time
void motorSystem_setTill(MotorSystem* target, Sensor* obs, int velocity, int val);	//run the motor system until the target sensor value has been reached
void motorSystem_setTillPID(MotorSystem* target, Sensor* obs, double k, int val);		//run motor system until a target sensor value has been reached with PID
void motorSystem_free(MotorSystem* target);																					//free dynamic memmory of motor system
// ---------------------------------------- Sensor ---------------------------------------------

//I2C
#define IME	  0	//integrated motor encoder

//analog sensors
#define GYRO  2	//gyroscope
#define ACCEL 3	//accelerometer
#define USRF  4	//ultrasonic range finder
#define POT   5	//potentiometer
#define LINE  6	//line sensor
#define LIGHT 7	//light sensor

//digital sensors
#define QME	  1  //2-wire quadrature motor encoder
#define BUMP  8	 //bumper switch
#define LIM   9	 //limit switch
#define LED   10 //LED indicator
#define SOL   11 //electronic pneumatic solenoid

Sensor sensor_init(int sensorType, const int port, ...);	//initialize the sensor
void sensor_set(Sensor* target, int value);								//set the value of the sensor
void sensor_reset(Sensor* target);												//reset sensor
bool sensor_opposite(Sensor* target);											//make the sensor return opposite values
bool sensor_isOpposite(Sensor target);										//return if the sensor has been set to return opposite values
int sensor_getType(Sensor target);												//retrieve the type of the sensor
int sensor_getSize(Sensor target);												//retrieve the number of ports the sensor uses
int sensor_getValue(Sensor target);												//retrieve the current sensor value
bool sensor_isAnalog(Sensor target);											//see if the sensor is digital or analog
void sensor_free(Sensor* target);													//free dynamic memmory of sensor

// ------------------------------------- Sensor System -----------------------------------------

bool sensorSystem_contains(SensorSystem target, Sensor sensor);						//check to see if the sensor system contains the sensor
SensorSystem sensorSystem_init(const int sensors, Sensor* sensor, ...);		//initialize the sensor system
void sensorSystem_set(SensorSystem* target, int value);										//set the value of the sensor system
void sensorSystem_reset(SensorSystem* target);														//reset sensor system
int sensorSystem_getSize(SensorSystem target);														//retrieve the number of ports the sensor uses
int sensorSystem_getValue(SensorSystem target);														//retrieve the average current sensor value
void sensorSystem_free(SensorSystem* target);															//free dynamic memmory of sensor system

// ------------------------------------------ LCD ----------------------------------------------

#define ON	   true		//used to turn lcd backlight on
#define OFF    false	//used to turn lcd backlight off
#define TOP    1			//first line of lcd
#define BOTTOM 2			//second line of lcd

LCD lcd_init(FILE* port);																																//initialize the lcd
FILE* lcd_getPort(LCD lcd);																															//return the port the lcd is using
char* lcd_getLine(LCD* lcd, unsigned char line);																				//return the first line that is written on the lcd
void lcd_clearLine(LCD* lcd, unsigned char line);																				//clear a line of the lcd
void lcd_clear(LCD* lcd);																																//clear everything on the lcd
void lcd_print(LCD* lcd, unsigned char line, const char* buffer);												//print a string on the specified line of the lcd
void lcd_printAt(LCD* lcd, unsigned char line, unsigned char pos, const char* buffer);	//print a string on the specified line at a specified location of the lcd
void lcd_centerPrint(LCD* lcd, unsigned char line, const char* buffer);									//center print a string on the specified line of the lcd
int lcd_buttonPressed(LCD lcd);																													//get the current button being pressed
bool lcd_buttonIsPressed(LCD lcd, int btn);																							//return true if the target button is being pressed
void lcd_waitForRelease(LCD lcd);																												//wait for the button to be released
bool lcd_backLightIsOn(LCD lcd);																												//return state of the lcd backlight
void lcd_backLight(LCD* lcd, bool state);																								//change state of lcd backlight

#endif /* NDAPI_H_ */
