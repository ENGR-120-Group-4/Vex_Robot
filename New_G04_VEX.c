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

// To stop the main while loop
cont = 1;

////////////////////////////////////////////////////////////////////////////////
// Put your functions under here

void flipX()
  if ((SensorValue[xmin] || SensorValue[xmax]) == 1){
	   motor[xMotor] = motor[xMotor]*-1;
     return motor[xMotor];
}

int xmax() {
	if (SensorValue[xmax] == 0) {
		return 1;
	 } else {
		return 2;
}


int xmin() {
	if (SensorValue[xmin] == 0) {
		return 1;
	} else {
		return 3;
	}

/*
  Function: void yInc()
  Increment the Y motor by 1cm, it should make sure that make that yMax is not depressed

  Parameters: None

  Returns: None
 */
void yInc(){
  motor[yMotor] = 20;
  wait1Msec(1000 * onecm);
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
  motor[xMotor] = 0
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
      case 1:
        // Nothing pressed
        break;
      //xMax depressed
      case 2:
        //Flip X speed and increment
        break;
      //xMin depressed
      case 3:
        //Flip X speed and increment
        break;
      //yMax depressed
      case 5:
        break;
      //yMin depressed
      case 7:
        // Nothing just go to xMax
        break;
      //xMax and yMax depressed
      case 10:
        break;
      //xMax and yMin
      case 14:
        //Same thing as xMax or xMin
        break;
      //xMin and yMax depressed and ended
      case 15:
        motor[xMotor] = 0;
        motor[yMotor] = 0;
        /*
         * Next code after completion of scanning
         * More specific code can be added to go to the dots, logic can be added
         * in order to get directly to them in a secondary function
         */
        break;
      case 21:
        //Start the code after zeroing
        break;
      default:
        break;
    }
  }
}
