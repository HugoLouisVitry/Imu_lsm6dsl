#include <Arduino.h>
// Includes.

#include "../lib/metro.h"
#include "imu.h"


// Components.
#define SerialPort Serial
#define I2C2_SCL    PB8 //old = PB10
#define I2C2_SDA    PB9 //old = PB11
#define INT1        PA4 //old = PD11

TwoWire dev_i2c(I2C2_SDA, I2C2_SCL);
LSM6DSLSensor LSM(&dev_i2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW);
IMU imu(&LSM);
Metro timer(50);

float angle[3];
float offset[4];

int32_t gyr[3];
void setup() {

  // Led.
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial for output.
  SerialPort.begin(9600);
  SerialPort.println("Démarage");

  // Initialize I2C bus.
  dev_i2c.begin();

  // Initlialize Components.
  imu.init_gyro();
  imu.is_gyr_calibrated(offset);
  if (offset[0])
  {
    SerialPort.print("\nCalibrated: ");
    SerialPort.print(offset[0]);
    SerialPort.print(" offset_x: ");
    SerialPort.print(offset[1]);
    SerialPort.print(" offset_y: ");
    SerialPort.print(offset[2]);
    SerialPort.print(" offset_z: ");
    SerialPort.print(offset[3]);
    SerialPort.println();
  }
  else{SerialPort.println("Error please Reload");}

  SerialPort.println("Ok !");
  delay(2000);
}


void loop() {

  if(timer.check())
  {
    imu.update_ang_pos();
    imu.get_ang_pos(angle);
    SerialPort.print("\nTheta_x: ");
    SerialPort.print(angle[0]);
    SerialPort.print(" Theta_y: ");
    SerialPort.print(angle[1]);
    SerialPort.print(" Theta_z: ");
    SerialPort.print(angle[2]);
    SerialPort.println();
  }
  
} 



