#include <NDAPI.h>

// -------------------------------------- Motor ------------------------------------------------

/*
 * Set the port for the motor.
 *
 * @param port The desired port for the motor.
 * @param isReversed Flag to tell if motor should be reversed.
 * @return The motor being initialized.
 */
Motor motor_init(int port, bool isReversed){
	Motor tmp;									//motor being returned
	tmp.reversed = isReversed;	//set the reversed flag
	tmp.port = port;						//set the motor port
	motor_stop(&tmp);						//set motor velocity to zero

	return tmp;
}

/*
 * Set reversed flag to its opposite.
 *
 * @param target The motor being manipulated.
 * @return The current reversed motor state.
 */
bool motor_reverse(Motor* target){
	target->reversed = !target->reversed;
	return target->reversed;
}

/*
 * Set the velocity of the motor.
 *
 * @param target The motor being manipulated.
 * @param velocity The desired velocity of the motor.
 */
void motor_setVelocity(Motor* target, int velocity){

	//input velocity is over max limit
	if(velocity > 127)
		velocity = 127;

	//input velocity is below min limit
	else if(velocity < -127)
		velocity = -127;

	target->velocity = velocity;	//assign the velocity for the motor

	//reversed
	if(target->reversed)
		motorSet(target->port, -target->velocity);	//set the velocity for the motor

	//not reversed
	else
		motorSet(target->port, target->velocity);	//set the velocity for the motor
}

/*
 * Get the velocity of the motor.
 *
 * @param target The motor being accessed.
 * @return The current velocity of the motor.
 */
int motor_getVelocity(Motor target){
	return target.velocity;
}

/*
 * Get the port of the motor.
 *
 * @param target The motor being accessed.
 * @return The port of the motor.
 */
int motor_getPort(Motor target){
	return target.port;
}

/*
 * Get the reversed flag of the motor.
 *
 * @param target The motor being accessed.
 * @return The reversed state of the motor.
 */
bool motor_isReversed(Motor target){
	return target.reversed;
}

/*
 * Set the velocity of the motor to zero.
 *
 * @param target The motor being manipulated.
 */
void motor_stop(Motor* target){
	motor_setVelocity(target, 0);	//set the velocity of the motor to zero
}

/*
 * Run motor for a certain amount of time.
 *
 * @param target The motor being manipulated.
 * @param velocity The desired motor velocity.
 * @param time The amount of time to run the motor in milliseconds.
 */
void motor_setFor(Motor* target, int velocity, unsigned int time){
	motor_setVelocity(target, velocity);	//set motor velocity
	delay(time);													//run motor for desired amount of time
	motor_stop(target);										//stop the motor
}

/*
 * Run motor until a target sensor value has been reached.
 *
 * @param target The motor being manipulated.
 * @param obs The sensor that stops the motor.
 * @param velocity The velocity the motor should run at.
 * @param val The target value of the sensor.
 */
void motor_setTill(Motor* target, Sensor* obs, int velocity, int val){
	motor_setVelocity(target, velocity);	//set motor velocity
	while(sensor_getValue(*obs) != val);	//run motor until sensor value is reached
	motor_stop(target);										//stop motor
}

/*
 * Run motor until a target sensor value has been reached with PID.
 *
 * @param target The motor being manipulated.
 * @param obs The sensor that stops the motor.
 * @param k The PID constant.
 * @param val The target value of the sensor.
 */
void motor_setTillPID(Motor* target, Sensor* obs, double k, int val){

	//update motor in PID loop until sensor target value is near
	while(abs(sensor_getValue(*obs)) != val || (val - sensor_getValue(*obs)) * k < 10)
		motor_setVelocity(target, (val - sensor_getValue(*obs)) * k );

	motor_stop(target);	//stop motor
}

// ------------------------------------ Motor System -------------------------------------------

/*
 *	Check to see if the motor system contains the motor.
 *
 *	@param target The motor system being evaluated.
 *	@param m The motor being searched for.
 *	@return If the motor system contains the motor.
 */
bool motorSystem_contains(MotorSystem target, Motor m){

	//search for motor
	for(int i = 0; i < motorSystem_getSize(target); i++)
		if(target.motors[i].port == m.port)
			return true;
	return false;
}

/*
 *	Assign motors to the motor system.
 *
 *	@param motors The amount of motors to be added to the motor system.
 *	@param m The motor being assigned to the motor system.
 *	@param ... Motors being assigned to the motor system.
 *	@return The motor system being initialized.
 */
MotorSystem motorSystem_init(const int motors, Motor* m, ...){

	va_list param;			//create list of parameters
	va_start(param, m);	//start list of parameters

	MotorSystem tmp;																												//motor system being returned
	tmp.size = motors;																											//set the size to zero
	tmp.motors = (Motor*)malloc(motorSystem_getSize(tmp) * sizeof(Motor));	//allocate memmory for motor system

	//assign motors
	for(int i = 0; i < motorSystem_getSize(tmp); i++){

		//add the new motor
		if(m->port > 0 && m->port <= 10 && !motorSystem_contains(tmp, *m))
			tmp.motors[i] = *m;

		m = va_arg(param, Motor*);	//get the next parameter
	}

	va_end(param);					//end the list of parameters
	motorSystem_stop(&tmp);	//stop all motors in the motor system
	return tmp;
}

/*
 *	Set the velocity of the motor system.
 *
 *	@param target The motor system being manipulated.
 *	@param velocity The new velocity for the motor system.
 */
void motorSystem_setVelocity(MotorSystem* target, int velocity){

	//input velocity is over max limit
	if(velocity > 127)
		velocity = 127;

	//input velocity is below min limit
	else if(velocity < -127)
		velocity = -127;

	target->velocity = velocity;	//set the new motor system velocity

	//set the new velocity for the motors
	for(int i = 0; i < target->size; i++)
			motor_setVelocity(&target->motors[i], target->velocity);
}

/*
 *	Retrieve the velocity of the motor system.
 *
 *	@param target The motor system being accessed.
 *	@return The velocity of the motor system.
 */
int motorSystem_getVelocity(MotorSystem target){
	return target.velocity;
}

/*
 *	Retrieve the size of the motor system.
 *
 *	@param target The motor system being accessed.
 *	@return The size of the motor system.
 */
int motorSystem_getSize(MotorSystem target){
	return target.size;
}

/*
 *	Set the velocity of the motor system to zero.
 *
 *	@param target The motor system being manipulated.
 */
void motorSystem_stop(MotorSystem* target){
	motorSystem_setVelocity(target, 0);		//set motor system velocity to zero
}

/*
 * Run the motor system for a desired amount of time.
 *
 * @param target The motor system being manipulated.
 * @param velocity The desired velocity for the motor system to run at.
 * @param time The desired amount of time for the motor system to run for.
 */
void motorSystem_setFor(MotorSystem* target, int velocity, unsigned int time){
	motorSystem_setVelocity(target, velocity);	//set motor system to desired velocity
	delay(time);																//run the motor system for the desired amount of time
	motorSystem_stop(target);										//stop the motor system
}

/*
 * Run the motor system until a target sensor value has been reached.
 *
 * @param target The motor system being manipulated.
 * @param obs The sensor that stops the motor system.
 * @param velocity The velocity the motor should run at.
 * @param val The target value of the sensor.
 */
void motorSystem_setTill(MotorSystem* target, Sensor* obs, int velocity, int val){
	motorSystem_setVelocity(target, velocity);	//set motor system velocity
	while(sensor_getValue(*obs) != val);				//run motor system until sensor value is reached
	motorSystem_stop(target);										//stop motor system
}

/*
 * Run the motor system until a target sensor value has been reached using PID.
 *
 * @param target The motor system being manipulated.
 * @param obs The sensor that stops the motor system.
 * @param k The PID constant.
 * @param val The target value of the sensor.
 */
void motorSystem_setTillPID(MotorSystem* target, Sensor* obs, double k, int val){

	//update motor system in PID loop until sensor target value is near
	while(abs(sensor_getValue(*obs)) != val || (val - sensor_getValue(*obs)) * k < 10)
		motorSystem_setVelocity(target, (val - sensor_getValue(*obs)) * k );

	motorSystem_stop(target);	//stop motor system
}

/*
 * Free the allocated memmory stored in the motor vector of the motor system.
 *
 * @param target The motor system being freed.
 */
void motorSystem_free(MotorSystem* target){
	free(target->motors);
}

// ---------------------------------------- Sensor ---------------------------------------------

/*
 * Set up and initialize the sensor.
 *
 * @param sensorType The type of sensor being initialized.
 * @param port The desired port for the motor.
 * @param ... The desired ports for the motor or the multiplier if it is a gyro sensor.
 * @return The sensor being initialized.
 */
Sensor sensor_init(int sensorType, int port, ...){

	va_list param;					//create list of parameters
	va_start(param, port);	//start list of parameters

	Sensor tmp;							//sensor being returned
	tmp.type = sensorType;	//set the sensor type
	tmp.size = 0;						//set the size to zero
	tmp.opposite = false;		//lower opposite flag

	//sensor uses 2 ports or is a GYRO
	if(sensor_getType(tmp) == QME || sensor_getType(tmp) == USRF)
		tmp.size = 2;

	//sensor uses 1 port
	else
		tmp.size = 1;

	tmp.ports = (int*)malloc(sizeof(int) * sensor_getSize(tmp));	//allocate memmory for motor system

	//assign ports
	for(int i = 0; i < sensor_getSize(tmp); i++){
		tmp.ports[i] = port;				//add the new sensor
		port = va_arg(param, int);	//get the next parameter
	}

	//initialize gyro sensor
	if(sensor_getType(tmp) == GYRO){
		tmp.sensor = gyroInit(tmp.ports[0], va_arg(param, int));	//set sensor to Gyro with user defined multiplier
		tmp.analog = true;																				//is an analog sensor
	}

	//initialize integrated motor encoder on I2C
	else if(tmp.type == IME){
		tmp.sensor = NULL;	//set the sensor to null
		tmp.analog = false;	//not an analog sensor
		imeInitializeAll();	//initialize all IME
	}

	//initialize quadrature motor encoder
	else if(tmp.type == QME){
		tmp.sensor = encoderInit(tmp.ports[0], tmp.ports[1], tmp.opposite);	//set sensor to be an encoder
		tmp.analog = false;																									//not an analog sensor
	}

	//initialize ultrasonic range finder
	else if(tmp.type == USRF){
		tmp.sensor = ultrasonicInit(tmp.ports[0], tmp.ports[1]);	//set sensor to be an ultrasonic range finder
		tmp.analog = false;																				//not an analog sensor
	}

	//intialize standard analog input sensor type
	else if(tmp.type >= POT && tmp.type <= LIGHT){
		tmp.sensor = NULL;										//set the sensor to null
		pinMode(tmp.ports[0], INPUT_ANALOG);	//set up IO port for analog reading
		tmp.analog = true;										//is an analog sensor
	}

	//initialize standard digital input sensor type
	else if(tmp.type >= BUMP && tmp.type <= LIM){
		tmp.sensor = NULL;							//set the sensor to null
		pinMode(tmp.ports[0], INPUT);		//set up IO port for digital reading
		tmp.analog = false;							//not an analog sensor
	}

	//initialize standard digital input sensor type
	else if(tmp.type == LED || tmp.type == SOL){
		tmp.sensor = NULL;							//set the sensor to null
		pinMode(tmp.ports[0], OUTPUT);	//set up IO port for digital writing
		tmp.analog = false;							//not an analog sensor
	}

	va_end(param);			//end the list of parameters
	sensor_reset(&tmp);	//reset the sensor
	return tmp;
}

/*
 * Set the sensor's value.
 * Only affects digital sensors.
 *
 * @param target The sensor being manipulated.
 * @param value The value to which the sensor will be set.
 */
void sensor_set(Sensor* target, int value){
	if(!sensor_isAnalog(*target))
		digitalWrite(target->ports[0], value);
}

/*
 * Set the sensor's value to zero.
 * Does not affect analog sensors.
 *
 * @param target The sensor being manipulated.
 */
void sensor_reset(Sensor* target){

	//reset integrated motor encoder
	if(target->type == IME)
		imeReset(target->ports[0]);

	//reset 2-wire quadrature motor encoder
	else if(target->type == QME)
		encoderReset(target->sensor);

	//reset gyro
	else if(target->type == GYRO)
		gyroReset(target->sensor);

	//reset other sensors (regular analog sensors cannot be reset)
	else if(!sensor_isAnalog(*target))
		sensor_set(target, 0);
}

/*
 * Set the sensor's opposite flag to its opposite.
 *
 * @param target The sensor being manipulated.
 * @return The state of the opposite flag.
 */
bool sensor_opposite(Sensor* target){
	target->opposite = !target->opposite;	//reverse opposite

	//the sensor is a quadrature motor encoder
	if(target->type == QME)
		target->sensor = encoderInit(target->ports[0], target->ports[1], target->opposite);

	return target->opposite;
}

/*
 * Retrieve the state of the opposite flag.
 *
 * @param target The sensor being manipulated.
 * @return The state of the opposite flag.
 */
bool sensor_isOpposite(Sensor target){
	return target.opposite;
}

/*
 * Retrieve the type of the sensor.
 *
 * @param target The sensor being manipulated.
 * @return The sensor type.
 */
int sensor_getType(Sensor target){
	return target.type;
}

/*
 * Retrieve the amount of ports the sensor uses.
 *
 * @param target The sensor being manipulated.
 * @return The amount of ports the sensor uses.
 */
int sensor_getSize(Sensor target){
	return target.size;
}

/*
 * Retrieve the current value of the sensor.
 *
 * @param target The sensor being manipulated.
 * @return The most current sensor value.
 */
int sensor_getValue(Sensor target){

	//integrated motor encoder
	if(target.type == IME){
		int value = 0;										//holds integrated motor encoder value
		imeGet(target.ports[0], &value);	//retrieve value from integrated motor encoder
		return value;
	}

	//2-wire quadrature motor encoder
	else if(target.type == QME)
		return encoderGet(target.sensor);

	//ultrasonic sensor
	else if(target.type == USRF)
		return ultrasonicGet(target.sensor);

	//analog sensor
	else if(sensor_isAnalog(target))
		return analogRead(target.ports[0]);

	//digital sensor
	else
		return digitalRead(target.ports[0]);
}

/*
 * Retrieve the state of the analog flag.
 *
 * @param target The sensor being manipulated.
 * @return The state of the analog flag.
 */
bool sensor_isAnalog(Sensor target){
	return target.analog;
}

/*
 * Free the allocated memmory from the sensor.
 *
 * @param target The sensor whose ports are being freed.
 */
void sensor_free(Sensor* target){
	free(target->ports);
}

// ------------------------------------- Sensor System -----------------------------------------

/*
 *	Check to see if the sensor system contains the sensor.
 *
 *	@param target The sensor system being evaluated.
 *	@param sensor The sensor being searched for.
 *	@return If the sensor system contains the sensor.
 */
bool sensorSystem_contains(SensorSystem target, Sensor sensor){

	//search for sensor
	for(int i = 0; i < sensorSystem_getSize(target); i++)
		if(sensor_getType(target.sensors[i]) == sensor_getType(sensor))
			if(target.sensors[i].ports[0] == sensor.ports[0])
				return true;
	return false;
}

/*
 *	Assign sensors to the sensor system.
 *
 *	@param sensors The total number of sensors that are being put into the system.
 *	@param sensor The sensor being assigned to the sensor system.
 *	@param ... Sensors being assigned to the sensor system.
 *	@return The sensor system being initialized.
 */
SensorSystem sensorSystem_init(const int sensors, Sensor* sensor, ...){

	va_list param;						//create list of parameters
	va_start(param, sensor);	//start list of parameters

	SensorSystem tmp;																														//sensor system being returned
	tmp.size = sensors;																													//set the size of sensor system
	tmp.sensors = (Sensor*)malloc(sensorSystem_getSize(tmp) * sizeof(Sensor));	//allocate memmory for sensor system

	//assign sensor ports
	for(int i = 0; i < sensorSystem_getSize(tmp); i++){

		//port being added is valid
		if(sensorSystem_contains(tmp, *sensor)){
			i--;					//decrease iterator
			tmp.size--;		//decrease number of sensors in sensor system
		}

		//add the new sensor
		else
			tmp.sensors[i] = *sensor;

		sensor = va_arg(param, Sensor*);	//get the next parameter
	}

	va_end(param);						//end the list of parameters
	sensorSystem_reset(&tmp);	//reset all the sensors in the sensor system
	return tmp;
}

/*
 * Set the sensor values in the system to the desired value.
 *
 * @param target The sensor system being manipulated.
 * @param value The value the sensors in the system are being set to.
 */
void sensorSystem_set(SensorSystem* target, int value){

	//set the value of the sensor system
	for(int i = 0; i < sensorSystem_getSize(*target); i++)
		sensor_set(&target->sensors[i], value);
}

/*
 * Reset all sensors in the system to the desired value.
 *
 * @param target The sensor system being manipulated.
 */
void sensorSystem_reset(SensorSystem* target){

	//reset sensor system
	for(int i = 0; i < sensorSystem_getSize(*target); i++)
		sensor_reset(&target->sensors[i]);
}

/*
 * Retrieve the number of ports the sensor uses.
 *
 * @param target The sensor system being manipulated.
 * @return The number of sensors in the system.
 */
int sensorSystem_getSize(SensorSystem target){
	return target.size;
}

/*
 * Retrieve the average current sensor value.
 *
 * @param target The sensor system being manipulated.
 * @return The average current sensor value.
 */
int sensorSystem_getValue(SensorSystem target){

	//no sensors to pull values from
	if(sensorSystem_getSize(target) == 0)
		return 0;

	int value = 0;	//the sum of all the sensor values

	//get the sum of the sensor values
	for(int i = 0; i < sensorSystem_getSize(target); i++)
		value += sensor_getValue(target.sensors[i]);

	return value / sensorSystem_getSize(target);	//return the average sensor value
}

/*
 * Free the sensors from the sensor system. This will not free the data
 * allocation from the sensors that are apart of the system.
 *
 * @param target The sensor sytem whose sensors are being freed.
 */
void sensorSystem_free(SensorSystem* target){
	free(target->sensors);
}
// ------------------------------------------ LCD ----------------------------------------------

/*
 * Initialize the lcd.
 *
 * @param port The port the lcd is assigned to.
 * @return The initialized lcd.
 */
LCD lcd_init(FILE* port){
	LCD tmp;									//temporary lcd that will be returned;
	tmp.port = port;					//set lcd port
	lcdInit(tmp.port);				//initialize the lcd
	lcd_clear(&tmp);					//clear the lcd
	lcd_backLight(&tmp, ON);	//turn on the lcd backlight

	return tmp;
}

/*
 * Retrieve the port the lcd is using.
 *
 * @param lcd The lcd being manipulated.
 * @return The port that the lcd is using.
 */
FILE* lcd_getPort(LCD lcd){
	return lcd.port;
}

/*
 * Retrieve what was last written on the desired
 * line of the lcd.
 *
 * @param lcd The lcd being manipulated.
 * @param line The line being retrieved.
 * @return What was last written on the desired line of the lcd.
 */
char* lcd_getLine(LCD* lcd, unsigned char line){

	//retrieve first line
	if(line == TOP)
		return lcd->line1;

	//retrieve second line
	else if(line == BOTTOM)
		return lcd->line2;

	//invalid line number
	else
		return NULL;
}

/*
 * Clear the text from the designated line of the lcd.
 *
 * @param lcd The lcd being manipulated.
 * @param line The line being cleared.
 */
void lcd_clearLine(LCD* lcd, unsigned char line){

	//clear first line
	if(line == TOP){
		for(int i = 0; i < 16; i++)
			lcd->line1[i] = ' ';
		lcdSetText(lcd->port, line, lcd->line1);
	}

	//clear second line
	else if(line == BOTTOM){
		for(int i = 0; i < 16; i++)
			lcd->line2[i] = ' ';
		lcdSetText(lcd->port, line, lcd->line2);
	}
}

/*
 * Clear the text from the entire lcd.
 *
 * @param lcd The lcd being manipulated.
 */
void lcd_clear(LCD* lcd){
	lcd_clearLine(lcd, TOP);	//clear first line
	lcd_clearLine(lcd, BOTTOM);	//clear second line
}

/*
 * Print to a specified line of the lcd.
 *
 * @param lcd The lcd being manipulated.
 * @param line The line being written to.
 * @param buffer The text being written to the designated line.
 */
void lcd_print(LCD* lcd, unsigned char line, const char* buffer){

	//set text for first line
	if(line == TOP){
		lcd_clearLine(lcd, TOP);	//clear first line

		//copy buffer into first line
		for(int i = 0; i < 16 && buffer; i++)
			lcd->line1[i] = buffer[i];

		lcdSetText(lcd->port, line, lcd->line1);	//set the text on the lcd
	}

	//set text for second line
	else if(line == BOTTOM){
		lcd_clearLine(lcd, BOTTOM);	//clear second line

		//copy buffer into second line
		for(int i = 0; i < 16 && buffer; i++)
			lcd->line2[i] = buffer[i];

		lcdSetText(lcd->port, line, lcd->line2);	//set the text on the lcd
	}
}

/*
 * Print a string on the specified line at a specified location of the lcd.
 *
 * @param lcd The lcd being manipulated.
 * @param line The line being written to.
 * @param pos The position to start the text.
 * @param buffer The text being written to the designated line.
 */
void lcd_printAt(LCD* lcd, unsigned char line, unsigned char pos, const char* buffer){

	//set text for first line
	if(line == TOP){
		lcd_clearLine(lcd, TOP);	//clear first line

		//copy buffer into first line
		for(int i = pos; i < 16 && buffer; i++)
			lcd->line1[i] = buffer[i-pos];

		lcdSetText(lcd->port, line, lcd->line1);	//set the text on the lcd
	}

	//set text for second line
	else if(line == BOTTOM){
		lcd_clearLine(lcd, BOTTOM);	//clear second line

		//copy buffer into second line
		for(int i = pos; i < 16 && buffer; i++)
			lcd->line2[i] = buffer[i-pos];

		lcdSetText(lcd->port, line, lcd->line2);	//set the text on the lcd
	}
}

/*
 * Center print a string on the specified line of the lcd.
 *
 * @param lcd The lcd being manipulated.
 * @param line The line being written to.
 * @param buffer The text being written to the designated line.
 */
void lcd_centerPrint(LCD* lcd, unsigned char line, const char* buffer){

	int start = (16 - strlen(buffer)) / 2;	//starting position for centering

	//too big to center
	if(start >= 16)
		start = 0;

	//set text for first line
	if(line == TOP)
		lcd_printAt(lcd, TOP, start, buffer);

	//set text for second line
	else if(line == BOTTOM)
		lcd_printAt(lcd, BOTTOM, start, buffer);
}

/*
 * Retrieve the button on the lcd that is being
 * pressed.
 *
 * @param lcd The lcd being manipulated.
 * @return The button being pressed.
 */
int lcd_buttonPressed(LCD lcd){
	delay(25);												//delay to allow lcd to read button
	return lcdReadButtons(lcd.port);
}

/*
 * See if the target button is being pressed.
 *
 * @param lcd The lcd being manipulated.
 * @param btn The target button being observed.
 * @return The state of the button being pressed.
 */
bool lcd_buttonIsPressed(LCD lcd, int btn){
	return btn == lcd_buttonPressed(lcd);
}

/*
 * Pause the program until no lcd buttons are being
 * pressed.
 *
 * @param lcd The lcd being manipulated.
 */
void lcd_waitForRelease(LCD lcd){
	while(lcd_buttonPressed(lcd) != 0);
	delay(250);
}

/*
 * Return the state of the lcd's backlight.
 *
 * @param lcd The lcd being manipulated.
 * @retrun The state of the LCD's backlight.
 */
bool lcd_backLightIsOn(LCD lcd){
	return lcd.backLight;
}

/*
 * Change the state of the lcd's backlight.
 *
 * @param lcd The lcd being manipulated.
 * @param state The desired state of the lcd backlight.
 */
void lcd_backLight(LCD* lcd, bool state){
	lcd->backLight = state;									//alter lcd state
	lcdSetBacklight(lcd->port, lcd_backLightIsOn(*lcd));	//update lcd backlight
}
