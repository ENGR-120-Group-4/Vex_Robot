#pragma config(Sensor, in1, irSensor, sensorReflection)
#pragma config(Sensor, dgtl1,   yMax, sensorTouch)
#pragma config(Sensor, dgtl2,   yMin, sensorTouch)
#pragma config(Sensor, dgtl3,   xMin, sensorTouch)
#pragma config(Sensor, dgtl4,   xMax, sensorTouch)
#pragma config(Sensor, dgtl11,   LED, sensorLEDtoVCC)
#pragma config(Motor, port2,  xMotor, tmotorNormal, openLoop)
#pragma config(Motor, port3,  yMotor, tmotorNormal, openLoop)

//The power level of the motors
#define SPEED 30
//How many rotations to move one cm
#define ROTPERCM 3
//Time for moving 1cm
#define ONECM ((float)ROTPERCM * (1 / (float)SPEED) * 60000)
//Standard waitime
#define STANARDWAIT 2000
//Threshold for activating the on the black square
#define THRESHOLD 0.5

// To stop the main switch case for further development
int cont = 1;

////////////////////////////////////////////////////////////////////////////////
// Put your functions under here


/*
  Function: void zero()
  Sends the motors to xMin and yMin to begin scanning

  Parameters: none

  Returns: none
*/
void zero() {
  motor[yMotor] = -1 * SPEED;
  motor[xMotor] = -1 * SPEED;
  int xin = 0;
  int yin = 0;
  while(1){
    if(SensorValue[xMin] != 0){motor[xMotor]=0;xin=1;}
    if(SensorValue[yMin] != 0){motor[yMotor]=0;yin=1;}
    if (xin == 1 && yin == 1) {break;}
    wait1Msec(10);
  }
}


/*
  Function: int xmax()
  Monitors the state of the xmax sensor and returns a value based on that state

  Parameters: none

  Returns: 1 if sensor is not pressed, 2 if pressed
*/
int xmax() {
	if (SensorValue[xMax] == 0) {
		return 1;
	 } else {
		return 2;
  }
}


/*
  Function: int xmin()
  Monitors the state of the xmin sensor and returns a value based on that state

  Parameters: none

  Returns: 1 if sensor is not pressed, 3 if pressed
*/
int xmin() {
	if (SensorValue[xMin] == 0) {
		return 1;
	} else {
		return 3;
	}
}


/*
  Function: int ymax()
  Monitors the state of the yMax sensor and returns a value based on that state

  Parameters: none

  Returns: 1 if sensor is not pressed, 5 if pressed
*/
int ymax() {
  if (SensorValue[yMax] == 0) {
  	return 1;
  	} else {
  	return 5;
  }
}


/*
  Function: int ymin()
  Monitors the state of the yMax sensor and returns a value based on that state

  Parameters: none

  Returns: 1 if sensor  not pressed, 7 if pressed
*/
int ymin() {
	if (SensorValue[yMin] == 0) {
  	return 1;
  } else {
  	return 7;
	}
}


/*
  Function: void yInc()
  Increment the Y motor by 1cm, it should make sure that make that yMax is not depressed

  Parameters: None

  Returns: None
 */
void yInc(){
  resetMotorEncoder(yMotor);
  motor[yMotor] = SPEED;
  clearTimer(T2);
  while((time1[T2]< ONECM) && SensorValue[yMax] == 0){}
  motor[yMotor] = 0;
}


/*
  Function: void pause_yInc()
  Pauses the x motor then uses yInc() to increment the y then resumes the x motor

  Parameters: None

  Returns: None
 */
void pause_yInt(){
  short temp = motor[xMotor];
  motor[xMotor] = 0;
  yInc();
  motor[xMotor] = temp;
}


/*
  Function: void moveX(int dir)
  Moves the x motor left or right depending on dir

  Parameters:
  int dir -- Moves x to xMin if -1 and toward xMax if 1

  Returns: None
 */
void moveX(int dir) {
  motor[xMotor] = dir * SPEED;
  pause_yInt();
  wait1Msec(STANARDWAIT);
}


/*
  Function: void indicate()
  If the ir sensor is reading a value higher than the THRESHOLD light the LED

  Parameters: None

  Returns: None
 */
void indicate(){
  if (SensorValue[irSensor] < THRESHOLD){
    SensorValue[LED] = 1;
  }
  else{
    SensorValue[LED] = 0;
  }
}


////////////////////////////////////////////////////////////////////////////////
task main(){
  zero();
  while(1){
    // check if a dot is present (we can also track coordinates of the dots too)
    /*
     * Later cases without velocity changes can be removed without having issues
     * they will just go to the "default" case
     */
    indicate();
    //      2      3      5      7
    switch (xmax()*xmin()*ymax()*ymin()*cont) {
      case 0:
        // End the loop for further development
      	break;
      //xMax depressed
      case 2:
        moveX(-1);
        break;
      //xMin depressed
      case 3:
        moveX(1);
        break;
      case 10:
      	moveX(-1);
  			break;
      //xMax and yMin
      case 14:
        moveX(-1);
        break;
      //xMin and yMax depressed
      case 15:
        motor[xMotor] = 0;
        motor[yMotor] = 0;
        zero();
        /*
         * Next code after completion of scanning
         * More specific code can be added to go to the dots, logic can be added
         * in order to get directly to them in a secondary function
         */
        break;
      case 21:
        motor[xMotor] = SPEED;
        break;
    }
  }
}
