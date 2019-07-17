#include "Wire.h"


const int addr = 0x68;

uint16_t cal_int; 
int16_t temp; 
int acc_axis[4]; 
int gyro_axis[4]; 

float angle_pitch;
float angle_roll;
int32_t angle_yaw;
float angle_pitch_acc;
float angle_roll_acc;
long acc_x;
long acc_y;
long acc_z;
long acc_total_vector[1];

double gyro_axis_cal[4]; 
double gyro_pitch;
double gyro_roll;
double gyro_yaw;

void setup()
{
  Serial.begin(57600);
  Wire.begin();
  TWBR = 12;  // Set I2C frequency to 400kHz
  pinMode(LED_BUILTIN, OUTPUT);
  init_gyro();
  }

void loop()
{
  receive();
  filter();
  print_data();
  delay(1);
  }

void callibrate()
{
  Serial.println("Callibrating");
  for(cal_int = 0; cal_int < 2000 ; cal_int++)
  { if(cal_int % 50 == 0)
    digitalWrite(13,!digitalRead(13));
    receive();
    gyro_axis_cal[1] += gyro_axis[1];
    gyro_axis_cal[2] += gyro_axis[2];
    gyro_axis_cal[3] += gyro_axis[3];
    delay(3);
    
    }
    gyro_axis_cal[1] /= 2000;
    gyro_axis_cal[2] /= 2000;
    gyro_axis_cal[3] /= 2000;
   Serial.print("Gyro Callibrated");
   delay(1000);
  }
  

void init_gyro()
{
  Serial.println("Initializing gyro");
  
  Wire.begin();
  Wire.beginTransmission(addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.beginTransmission(addr);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  Wire.beginTransmission(addr);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  Serial.println("Gyro initialized");
  callibrate();

  }

void receive(){
  Wire.beginTransmission(addr);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(addr,14,true);
  while(Wire.available()<14);
   acc_axis[1] = Wire.read()<<8|Wire.read();
   acc_axis[2] = Wire.read()<<8|Wire.read();
   acc_axis[3] = Wire.read()<<8|Wire.read();
   temp = Wire.read()<<8|Wire.read();
   gyro_axis[1] = Wire.read()<<8|Wire.read();
   gyro_axis[2] = Wire.read()<<8|Wire.read();
   gyro_axis[3] = Wire.read()<<8|Wire.read();
  if (cal_int == 2000)
  gyro_axis[1] -= gyro_axis_cal[1];
  gyro_axis[2] -= gyro_axis_cal[2];
  gyro_axis[3] -= gyro_axis_cal[3];
}


void filter()
{
  angle_pitch += gyro_axis[1]*0.0000611;
  angle_roll += gyro_axis[2]*0.0000611;

  angle_pitch -= angle_roll*sin(gyro_axis[3]*0.000001066);
  angle_roll += angle_pitch*sin(gyro_axis[3]*0.000001066);
  
  acc_total_vector[0] = sqrt((acc_axis[1]*acc_axis[1])+(acc_axis[2]*acc_axis[2])+(acc_axis[3]*acc_axis[3]));

  angle_pitch_acc = asin((float)acc_axis[2]/acc_total_vector[0]*57.296);
  angle_roll_acc = asin((float)acc_axis[1]/acc_total_vector[0]*-57.296);
  
  }

void print_data()
{ 
  Serial.print("Pitch: ");
  Serial.print(angle_pitch,0);
  Serial.print(" || Roll: ");
  Serial.print(angle_roll,0);
  Serial.print(" || Yaw: ");
  Serial.println(gyro_axis[3]/65.5,0);
  }
