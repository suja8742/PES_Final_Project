# PES_Final_Project
Final Project for Principles of Embedded Software - Fall 2021. Project by Sudarshan J. 

Project Name:  Digital Angle Gauge
Hardware used: NXP FRDM KL25Z, MMA8451Q, Push Button on PTD->3.

Changes to original proposal:
- Was unable to implement sleep mode satisfactorily as the sampling rate caused the accelerometer to hang. 
- Have configured for 0-360 degree operation, resolving at green color and blinking in order to indicate target angle, 45 degrees. 
- The green LED will continously blink green if 45 degrees is maintained. Using this indicator, precise angles can be gauged. 
- The UART also prints the angle continously. 
- The LED resolves to green and becomes lighter green as the user moves away from the target angle. A little further away, it resolves to 
yellow. Farthest away, it resolves to Red color. 
- Implemented the calibration similar to the Wii motion sensing remote. Place the accelerometer stationary on a flat surface at 0 degrees. 
It calibrates the pitch to 0 degrees. 


Test: 

- Performed an I2C device_ID read test to check data integrity of the line. 
- Included free-run_test, color test and target angle testing for accelerometer. 
- Included test macro. 

Video Link: https://drive.google.com/drive/folders/1uiHm9tvubZJdDhW8brMyM3-YcHHXgdK8?usp=sharing

Original proposal included in Repo. 

