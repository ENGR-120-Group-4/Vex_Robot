#pragma config(Sensor, inl, irSensor, sensorReflection)
#pragma config(Sensor, dgt11, yMax, sensorTouch)
#pragma config(Sensor, dgt12, yMin, sensorTouch)
#pragma config(Sensor, dgt13, xMin, sensorTouch)
#pragma config(Sensor, dgt14, xMin, sensorTouch)
#pragma config(Motor, port2, xMotor, tmotorServoContinousRotation, openLoop)
#pragma config(Motor, port3, yMotor, tmotorServoContinousRotation, openLoop)

/*
 * If you want to attempt compiling c on your computer, you can install
 * https://atom.io/packages/gcc-make-run and https://jmeubank.github.io/tdm-gcc/
 * Compile using f6, this will always give you an error but it might show you
 * something useful
 */

// Global Variables to update for the storing of locations of the ir sensor
long xpos = 0;
long ypos = 0;

// Just moves the robot arm left and right
// This code should not be used in the future, this is just for demonstration
int motor_x(int max, int min){
  if (max!=0||min!=0) {
    motor[xMotor] = motor[xMotor]*-1;
    return motor[xMotor];
  }
  else{
    return motor[xMotor];
  }
}


task main(){
  motor[xMotor] = 100;
  while(1){
    motor[xMotor] = motor_x(SensorValue[xMax],SensorValue[xMin])
    wait1Msec(1000);
  }

}
