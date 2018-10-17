#include "main.h"

bool turboMode = false;

#define lMotor1 3
#define lMotor2 4

#define rMotor1 2
#define rMotor2 5

#define intake1 6

#define conveyor1 1

#define flyWheel1 7
#define flyWheel2 8

void lDriveSet(int control) {
	motorSet(lMotor1, -control);
	motorSet(lMotor2, -control);
}
void rDriveSet(int control) {
	motorSet(rMotor1, -control);
	motorSet(rMotor2, -control);
}
void flyWheelSet(int control) {
	motorSet(flyWheel1, control);
	motorSet(flyWheel2, control);
}

void intakeSet(int control) {
	motorSet(intake1, control);
}

void conveyorSet(int control) {
	motorSet(conveyor1, control);
}

void operatorControl() {
	while (true) {
		if (!turboMode) {
			if (joystickGetAnalog(1, 3) > 5 || joystickGetAnalog(1, 3) < -5)
				lDriveSet(joystickGetAnalog(1,3)^3/25000);
			else
				lDriveSet(0);

			if (joystickGetAnalog(1, 2) > 5 || joystickGetAnalog(1, 2) < -5)
				rDriveSet(joystickGetAnalog(1,2)^3/25000);
			else
				rDriveSet(0);
		} else {
			if (joystickGetAnalog(1, 3) > 5 || joystickGetAnalog(1, 3) < -5)
				lDriveSet(joystickGetAnalog(1,3));
			else
				lDriveSet(0);

			if (joystickGetAnalog(1, 2) > 5 || joystickGetAnalog(1, 2) < -5)
				rDriveSet(joystickGetAnalog(1,2));
			else
				rDriveSet(0);
		}

		if (joystickGetDigital(1, 5, JOY_DOWN)) {
			intakeSet(127);
		} else {
			intakeSet(0);
		}

		if (joystickGetDigital(1, 5, JOY_UP)) {
			conveyorSet(127);
		} else {
			conveyorSet(0);
		}

		if (joystickGetDigital(1, 6, JOY_UP)) {
			flyWheelSet(127);
		} else if (joystickGetDigital(1, 6, JOY_DOWN)) {
			flyWheelSet(-127);
		} else {
			flyWheelSet(0);
		}

		/*if (joystickGetDigital(1, 6, JOY_DOWN)) {
			turboMode = true;
		} else {
			turboMode = false;
		}*/

		delay(25);

	}
}
