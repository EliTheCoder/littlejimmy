#include "main.h"
#include "ports.h"

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
