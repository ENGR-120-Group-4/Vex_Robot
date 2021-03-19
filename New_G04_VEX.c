#pragma config(Sensor, in1, irSensor, sensorReflection)
#pragma config(Sensor, dgtl1,   xMax, sensorTouch)
#pragma config(Sensor, dgtl2,   xMin, sensorTouch)
#pragma config(Sensor, dgtl3,   yMin, sensorTouch)
#pragma config(Sensor, dgtl4,   yMin, sensorTouch)
#pragma config(Motor, port2,  yMotor, tmotorServoContinousRotation, openLoop)
#pragma config(Motor, port3,  xMotor, tmotorServoContinousRotation, openLoop)

// For if you like the
#define False 0
#define True 1

//rpm
#define SPEED 20
//
#define ROTPERCM 3
//Time for moving 1cm
#define ONECM (ROTPERCM * (1 / SPEED) * 6000)

// To stop the main while loop
int cont = 1;

////////////////////////////////////////////////////////////////////////////////
// Put your functions under here

void zero(){
  while(SensorValue[xMin] == 0){
  motor[xMotor] = -20;
  }
  while(SensorValue[yMin] == 0) {
  motor[yMotor] = -20;
  }
}

void flipX() {
  if (SensorValue[xMin] != 0 || SensorValue[xMax] != 0) {
	   motor[xMotor] = motor[xMotor]*-1;
   }
 }

int xMax() {
	if (SensorValue[xMax] == 0) {
		return 1;
	 } else {
		return 2;
  }
}


int xMin() {
	if (SensorValue[xMin] == 0) {
		return 1;
	} else {
		return 3;
	}
}

/*
Function: int yMax()
Monitors the state of the yMax sensor and returns a value based on that state

Parameters: none

Returns: 1 if sensor is not pressed, 5 if pressed
*/
int yMax() {
  if (SensorValue[yMax] == 0) {
  	return 1;
  	} else {
  	return 5;
  }
}
/*
  Function: int yMin()
  Monitors the state of the yMax sensor and returns a value based on that state

  Parameters: none

  Returns: 1 if sensor  not pressed, 7 if pressed
*/
int yMin() {
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
  motor[yMotor] = 20;
  wait1Msec(ONECM);
  motor[yMotor] = 0;
}

/*
  Function: void pause_yInc()
  Pauses the x motor then uses yInc() to increment the y then resumes the x motor

  Parameters: None

  Returns: None
 */
void pause_yInt(){
  int temp = motor[xMotor];
  motor[xMotor] = 0;
  yInc();
  motor[yMotor] = temp;
}

////////////////////////////////////////////////////////////////////////////////
task main(){
  // Zero the robot
  while(1){
    // check if a dot is present (we can also track coordinates of the dots too)
    /*
     * Later cases without velocity changes can be removed without having issues
     * they will just go to the "default" case
     */
    //      2      3      5      7
    switch (xMax()*xMin()*yMax()*yMin()*cont) {
      case 0:
        // End the loop
      //xMax depressed
      case 2:
        flipX();
        pause_yInt();
        break;
      //xMin depressed
      case 3:
        flipX();
        pause_yInt();
        break;
      //yMax depressed
      //xMax and yMax depressed
      //xMax and yMin
      case 14:
        flipX();
        pause_yInt();
        break;
      //xMin and yMax depressed and ended
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
        motor[xMotor] = 20;
        break;
      default:
    }
  }
}
