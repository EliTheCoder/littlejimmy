#include "main.h"


void lDriveSet(int control){
	motorSet(2, -control);
	motorSet(1, -control);
}
void rDriveSet(int control){
	motorSet(8, -control);
	motorSet(10, -control);
}

void operatorControl() {
	while (true)
	{
		lDriveSet(joystickGetAnalog(1,3));

		rDriveSet(joystickGetAnalog(1,2));

		delay(25);

		if (joystickGetDigital(1, 6, JOY_UP)) {
				lDriveSet(20);
				rDriveSet(20);
				delay(1000);
		}

		if (joystickGetDigital(1, 7, JOY_DOWN)) {
				lDriveSet(127);
				rDriveSet(127);
				delay(500);
		}
	}
}
