#include "main.h"
#include "ports.h"
#include "methods.h"

void operatorControl() {
	while (true) {
		if (joystickGetAnalog(1, 3) > 5 || joystickGetAnalog(1, 3) < -5)
			lDriveSet(joystickGetAnalog(1,3)^3/25000);
		else
			lDriveSet(0);

		if (joystickGetAnalog(1, 2) > 5 || joystickGetAnalog(1, 2) < -5)
			rDriveSet(joystickGetAnalog(1,2)^3/25000);
		else
			rDriveSet(0);

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
		} else {
			if (joystickGetDigital(1, 6, JOY_DOWN)) {
				flyWheelSet(-127);
			} else {
				flyWheelSet(0);
			}
		}

		delay(25);

	}
}
