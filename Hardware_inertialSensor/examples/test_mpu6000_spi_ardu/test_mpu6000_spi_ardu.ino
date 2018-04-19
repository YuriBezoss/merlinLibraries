#include <Hardware_spi_ardu.h>
#include <Hardware_timer_ardu.h>
#include <Hardware_inertialSensor_mpu6000_spi.h>

Hardware_timer *timer;
Hardware_spi_ardu *spi;
Hardware_inertialSensor_mpu6000_spi *inertialSensor;

void setup(){
  Serial.begin(115200);
  timer = new Hardware_timer_ardu();
  spi = new Hardware_spi_ardu();
  inertialSensor = new Hardware_inertialSensor_mpu6000_spi(timer, spi);
}

void loop(){

  inertialSensor->update();

  Vector3f accel = inertialSensor->getAccel();
  Vector3f gyro = inertialSensor->getGyro();
  float temp = inertialSensor->getTemp();

  Serial.print(temp);
  Serial.print("\t");

  Serial.print("a_x: ");
  Serial.print(accel.x);
  Serial.print("\t a_y: ");
  Serial.print(accel.y);
  Serial.print("\t a_z: ");
  Serial.print(accel.z);

  Serial.print("\t\t g_x: ");
  Serial.print(gyro.x);
  Serial.print("\t g_y: ");
  Serial.print(gyro.y);
  Serial.print("\t g_z: ");
  Serial.print(gyro.z);

  Serial.println();
  delay(100);
}