#include "main.h"


void lDriveSet(int control){
	motorSet(2, -control);
	motorSet(1, -control);
}
void rDriveSet(int control){
	motorSet(3, -control);
	motorSet(4, -control);
}

void operatorControl() {
	while (true)
	{
		lDriveSet(joystickGetAnalog(1,3));

		rDriveSet(joystickGetAnalog(1,2));

		delay(25);

	}
}
