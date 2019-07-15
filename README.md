# Arduino----MPU6050
Print the angles out of MPU6050. Well, MPU6050 is a 3 axis gyroscope + 3 axis accelerometer with a temperature sensor and a Digital Motion Processing(DMP) unit. It uses the I2C connection.  

# Connections:
We are using Arduino Nano.<br>
To establish an I2C connection between Arduino and the sensor connect SDA and SCL (from MPU6050) to A4 and A5 (arduino) analog pins respectively. You can find SCL and SDA pins in Arduino Uno.  
MPU6050 --> Arduino  
1.  SCL --> A4  
2.  SDA --> A5  
3.  Vcc --> 5V  
4.  Gnd --> Gnd  

[Schematic](https://drive.google.com/open?id=1Ng9ZHCVDjGQ9TYUYfLGVWu6piD4Vy7HW)

# About the program
We're going to use *Wire.h* library for the I2C connection.  
