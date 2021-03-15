#pragma config(Sensor, in1, irSensor, sensorReflection)
#pragma config(Sensor, dgt11,   yMax, sensorTouch)
#pragma config(Sensor, dgt12,   yMin, sensorTouch)
#pragma config(Sensor, dgt13,   xMin, sensorTouch)
#pragma config(Sensor, dgt14,   xMin, sensorTouch)
#pragma config(Motor, port2,  xMotor, tmotorServoContinousRotation, openLoop)
#pragma config(Motor, port3,  yMotor, tmotorServoContinousRotation, openLoop)

#define False 0
#define True 1


/*
 * If you want to attempt compiling c on your computer, you can install
 * https://atom.io/packages/gcc-make-run and https://jmeubank.github.io/tdm-gcc/
 * Compile using f6, this will always give you an error but it might show you
 * something useful
 */

// Global Variables to update for the storing of locations of the ir sensor
double xpos = 0;
double ypos = 0;

int num_dots = 0;

/*
 * Function: void add_dots()
 * Adds 1 to the dot count
 *
 * Arguments: None
 *
 * Returns: none
 */
void add_dots(){
  if (irSensor!=0){num_dots++;//Should add the led here}
}


/*
 * Function: int xsensor()
 * If either of the x sensors are depressed return true(1) else false
 *
 * Arguments: None
 *
 * Returns: Boolean int of sensor value
 */
int xsensor(){
  //Returns True if hit
  if (SensorValue[xMax] != 0 || SensorValue[xMin] != 0 ){
    return 1;
  }
  //Returns False if not hit
  else{
    return 0;
  }

}

/*
 * Function int motor_x(int sensed)
 * Occilates the motor based on the value of the sensors
 *
 * Arguments:
 * int sensed -- if either of the sensors are detected then the power is
 * reversed
 *
 * Returns: int for the new power level
 *
 * Note: This could be made to not need to return a value
 */
int motor_x(int sensed){
  if (sensed) {
    motor[xMotor] = motor[xMotor]*-1;
    return motor[xMotor];
  }
  else{
    return motor[xMotor];
  }
}


/*
 * Function: void motor_y(int bottom,int speed)
 * Increments the y axis
 *
 * Arguments:
 * int bottom -- If the bottom y sensor is being pressed
 * int speed --  The speed of the ymotor
 *
 * Returns: Nothing
 */
void motor_y(int bottom,int speed){
  if (bottom!=0) {
    motor[yMotor] = 0;
  }
  else {
    motor[yMotor] = speed;
    // Time needs to be tweeked
    wait1Msec(10000);
    motor[yMotor] = 0;
  }
}

/*
 * Function: void zero()
 * Zeros the robot to both of the mins
 *
 * Arguments: None
 *
 * Returns: None
 */
void zero() {
  motor[yMotor] = -50;
  motor[xMotor] = -50;
  int xin = 0;
  int yin = 0;
  while(1){
    if(SensorValue[xMin] != 0){motor[xMotor]=0;xin=1;}
    if(SensorValue[yMin] != 0){motor[xMotor]=0;yin=1;}
    if (xin && yin) {break;}
    wait1Msec(1000);
  }
}


/*
 * Function: void dothethings()
 * Performs the logic to move the scan the area
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Note: This function should be removed and the contents put into main
 */
void dothethings() {
  int x_speed = 50;
  int y_speed = 50;
  motor[xMotor] = x_speed;
  zero();
  while(1){
    add_dots();
    switch (xsensor() + (SensorValue[yMax]!=0)) {
      case 2:
        zero();
      case 1:
        motor[xMotor] = 0;
        motor_y(SensorValue[yMax],y_speed)
        motor[xMotor] = motor_x(xsensor());
      case 0:
        motor[xMotor] = motor_x(xsensor());
    }
    wait1Msec(1000);
  }
}



task main(){
  dothethings();
  /*
  motor[xMotor] = 100;
  while(1){
    motor[xMotor] = motor_x(SensorValue[xMax],SensorValue[xMin])
    wait1Msec(1000);
  }
  */

}
