#include "main.h"

int lMotor1 = 1;
int lMotor2 = 2;

int rMotor1 = 3;
int rMotor2 = 4;

int flyWheel1 = 6;
int flyWheel2 = 7;

int intake1 = 5;

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
		} else {
			intakeActive = false;
		}

		if (joystickGetDigital(1, 6, JOY_UP)) {
			flyWheelActive = true;
		}

		if (joystickGetDigital(1, 7, JOY_RIGHT)) {
			speakerPlayRtttl("Super Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,"
   "8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
   "8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
   "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
   "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,8p.,"
   "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6," "8p,16d#6,8p,16d6,8p,16c6");
		}

		if (intakeActive) {
			intakeSet(127);
		} else {
			intakeSet(0);
		}

		if (flyWheelActive) {
			flyWheelSet(127);
		} else {
			flyWheelSet(0);
		}

		delay(25);

	}
}
