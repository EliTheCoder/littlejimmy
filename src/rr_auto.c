/*
 * @file rr_auto.c
 *
 * @brief The implementation of the record and rerun autonomous
 * 		  main methods and helper methods.
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

#include <rr_auto.h>
#include <main.h>

/*
 * Record the robots movements for a set amount of time.
 *
 * @param name The name of the file that the data will be
 * 			   be saved to. The file name is truncated to eight
 * 			   characters.
 * @param time The amount of time in milliseconds that should
 * 			   be recorded.
 */
void robot_record(const char* name, unsigned long int time){

	FILE* file = fopen(name, "w");	//initialize file pointer

	//count-down timer
	lcd_centerPrint(&Robot.lcd, TOP, "Recording in:");
	for(int i = 10; i > 0; i--){
		lcd_clearLine(&Robot.lcd, BOTTOM);
		lcdPrint(Robot.lcd.port, BOTTOM, "%d seconds", i);
		delay(1000);
	}

	lcd_centerPrint(&Robot.lcd, TOP, "Recording");	    //print to lcd

	//read motor values until record time is reached
	unsigned int counter = 0;
	if(file != NULL)
		while(counter < time){
			userControl();	//do normal drive functions

			//print time remaining onto the LCD
			lcd_clearLine(&Robot.lcd, BOTTOM);
			lcdPrint(Robot.lcd.port, BOTTOM, "T -%0.2f seconds", ((double)(time-counter)/1000));

			//write motor values
			for(int i = PORT_1; i <= PORT_10; i++)
				writeMotorValue(file, i);

			//write sensor values
			for(int i = DGTL_1; i <= DGTL_12; i++)
				writeDigitalPortValue(file, i);

			delay(20);		//delay required for recording
			counter += 20;	//increase counter
		}

	motorStopAll();										//stop all motors
	fclose(file);										//close the file stream
	lcd_centerPrint(&Robot.lcd, BOTTOM, "COMPLETED");	//print to lcd
	delay(1000);										//delay to read LCD message
}

/*
 * Replay the robots movements for a certain
 * alliance and position.
 *
 * @param name The name of the file being played back.
 * 		       The file name is truncated to eight
 * 			   characters.
 */
void robot_replay(const char* name){

	FILE* file = fopen(name, "r");	//initialize file pointer

	//continue to feed motor values until the end of the file
	if(file != NULL)
		while(!feof(file)){

			//set motor velocities
			for(int i = PORT_1; i <= PORT_10; i++)
				motorSet(i, readMotorValue(file));

			//set digital pin statuses
			for(int i = DGTL_1; i <= DGTL_12; i++)
				digitalWrite(i, readDigitalPortValue(file));

			delay(20);	//same delay as recording
		}
	motorStopAll();	//stop all motors
}

/*
 * Write the motor velocity value + 127 to the desired
 * file.
 *
 * @param file The file to write too.
 * @param motor The motor port whose velocity is being taken.
 */
void writeMotorValue(FILE* file, int port){
	int velocity = motorGet(port) + 127;
	char hex[2];

	//convert  to hexadecimal digit
	for(int i = 0; i < 2; i++){
			hex[i] = velocity % 16;
	    velocity = velocity / 16;
	}

	//write hexadecimal digit to file
	for(int i = 1; i >= 0; i--)
		fputc(itoc(hex[i]), file);
}

/*
 * Retrieve a motor value from the desired file.
 *
 * @param The velocity from the file.
 */
int readMotorValue(FILE* file){return (ctoi(fgetc(file))*16 + ctoi(fgetc(file)) - 127);}

/*
 * Write the state of the digital port to the desired
 * file.
 */
void writeDigitalPortValue(FILE* file, int port){fputc(itoc(digitalRead(port)), file);}

/*
 * Retrieve the digital port value from a file.
 *
 * @param The file being read from,
 * @return The numerical state of the digital port.
 */
int readDigitalPortValue(FILE* file){return ctoi(fgetc(file));}

/*
 * Convert a digit value to the ASCII equivalent.
 *
 * @param i A number between 0 and F.
 * @return The ASCII value of the digit.
 */
char itoc(int i){
	if(i < 10)
		return i + '0';				//number is a digit
	else
		return i - 10 + 'A';	//number is a letter
}

/*
 * Convert and ASCII value from '0' to 'F' to its integer equivalent.
 *
 * @param c The ACII character to be converted.
 * @return The integer value of the ASCII character.
 */
int ctoi(char c){
	if(c <= '9')
		return c - '0';				//character is a digit
	else
		return c + 10 - 'A';	//character is a letter
}
