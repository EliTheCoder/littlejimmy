#include "main.h"

int lMotor1 = 1;
int lMotor2 = 2;

int rMotor1 = 3;
int rMotor2 = 4;

int flyWheel1 = 5;
int flyWheel2 = 6;

int intake1 = 10;

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

bool intakeActive = false;
bool flyWheelActive = false;

void operatorControl() {
	while (true)
	{
		lDriveSet(joystickGetAnalog(1,3));

		rDriveSet(joystickGetAnalog(1,2));

		if (joystickGetDigital(1, 5, JOY_UP)) {
			intakeActive = true;
		}

		if (joystickGetDigital(1, 5, JOY_DOWN)) {
			intakeActive = false;
		}

		if (joystickGetDigital(1, 6, JOY_UP)) {
			flyWheelActive = true;
		}

		if (joystickGetDigital(1, 6, JOY_DOWN)) {
			flyWheelActive = false;
		}

		if (intakeActive) {
			intakeSet(127);
		}

		if (flyWheelActive) {
			flyWheelSet(127);
		}

		delay(25);

	}
}
