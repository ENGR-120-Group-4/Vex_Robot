#pragma config(Sensor, in1, irSensor, sensorReflection)
#pragma config(Sensor, dgtl1,   yMax, sensorTouch)
#pragma config(Sensor, dgtl2,   yMin, sensorTouch)
#pragma config(Sensor, dgtl3,   xMin, sensorTouch)
#pragma config(Sensor, dgtl4,   xMax, sensorTouch)
#pragma config(Motor, port2,  xMotor, tmotorServoContinousRotation, openLoop)
#pragma config(Motor, port3,  yMotor, tmotorServoContinousRotation, openLoop)

//rpm
#define SPEED 30
//
#define ROTPERCM 6
//Time for moving 1cm
#define ONECM (ROTPERCM * (1 / SPEED) * 6000)

// To stop the main while loop
int cont = 1;

////////////////////////////////////////////////////////////////////////////////
// Put your functions under here

int xin;
int yin;

void zero() {
  motor[yMotor] = -30;
  motor[xMotor] = -30;
  xin = 0;
  yin = 0;
  while(1){
    if(SensorValue[xMin] != 0){motor[xMotor]=0;xin=1;}
    if(SensorValue[yMin] != 0){motor[yMotor]=0;yin=1;}
    if (xin == 1 && yin == 1) {break;}
    wait1Msec(10);
  }
}

void flipX() {
  if (SensorValue[xMin] != 0 || SensorValue[xMax] != 0) {
	   motor[xMotor] = motor[xMotor]*-1;
   }
 }

int xmax() {
	if (SensorValue[xMax] == 0) {
		return 1;
	 } else {
		return 2;
  }
}


int xmin() {
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
int ymax() {
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
  motor[yMotor] = 20;
  wait1Msec(1000);
  motor[yMotor] = 0;
}

/*
  Function: void pause_yInc()
  Pauses the x motor then uses yInc() to increment the y then resumes the x motor

  Parameters: None

  Returns: None
 */
short temp;
void pause_yInt(){
  temp = motor[xMotor];
  motor[xMotor] = 0;
  yInc();
  motor[xMotor] = temp;
}

int c;

////////////////////////////////////////////////////////////////////////////////
task main(){
  zero();
  while(1){
    // check if a dot is present (we can also track coordinates of the dots too)
    /*
     * Later cases without velocity changes can be removed without having issues
     * they will just go to the "default" case
     */
    //      2      3      5      7
     c = xmax()*xmin()*ymax()*ymin();
    switch (xmax()*xmin()*ymax()*ymin()*cont) {
      case 0:
        // End the loop
      	break;
      //xMax depressed
      case 2:
        motor[xMotor] = -1 * SPEED;
        pause_yInt();
        wait1Msec(2000);
        break;
      //xMin depressed
      case 3:
        motor[xMotor] = SPEED;
        pause_yInt();
        wait1Msec(2000);
        break;
      //yMax depressed
      //xMax and yMax depressed
      //xMax and yMin
      case 14:
        motor[xMotor] = -1 * SPEED;
        wait1Msec(2000);
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
        motor[xMotor] = 30;
        break;
      default:
    }
  }
}
