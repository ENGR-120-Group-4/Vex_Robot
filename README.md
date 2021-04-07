# Vex_Robot
#### The group 4 ENGR 120 robot code, for scanning and locating dots on a 150mm x 100mm area
---------------------------------------------------------------------------------------
## Summary:

  Design an autonomous, touchless, surface disinfecting
robot that is capable of locating high-touch areas of
workbench equipment and disinfecting these surfaces
rapidly and thoroughly using radiation.

## Objectives
- Detect multiple black squares on a white paper
- Indicate every successful detection
- Count the number of black squares detected
- (Optional) Locate the black squares at a faster rate when scanning second time




## The Robot
![Screenshot 2021-03-13 011544](https://user-images.githubusercontent.com/54737724/111025725-e54a8300-839a-11eb-8592-02ba0c3b7af1.png)
---------------------------------------------------------------------------------------
## The Pinouts of the VEX ARM 32 Microcontroller
|Pin Info|Component Connected|
|-|-|
|Analog Port 1|Output of IR sensor (i.e. black square detection signal)|
|Digital Port 1|Limit switch on top y-axis (i.e. starting point for scanning)|
|Digital Port 2|Limit switch on bottom y-axis (i.e. ending point for scanning)|
|Digital Port 3|Limit switch on left x-axis (i.e. near the y-axis track)|
|Digital Port 4|Limit switch on right x-axis (i.e. away from the y-axis track)|
|Digital Port 11|Red colored LED|
|Motor Port 2|X-axis motor|
|Motor Port 3|Y-axis motor|

![Bot Logic (1)](https://user-images.githubusercontent.com/54737724/113948299-6261f000-97c1-11eb-92cf-08c761112efe.png)


