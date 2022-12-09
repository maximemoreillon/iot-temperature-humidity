/*
 * IoT temperature and humidity sensing module
 * 
 * Maxime MOREILLON
 * 
 * Board type: Wemos D1 Mini
 * 
 */

#include "IotKernel.h"
#include <DHT.h> 

#define DEVICE_TYPE "dht"
#define DEVICE_FIRMWARE_VERSION "0.1.0"
#define SENSOR_PIN D1
#define SENSOR_READ_PERIOD 10000


IotKernel iot_kernel(DEVICE_TYPE,DEVICE_FIRMWARE_VERSION); 
DHT sensor(SENSOR_PIN, DHT22);

void setup() {
  iot_kernel.init();
  sensor.begin();
}

void loop() {
  iot_kernel.loop();
  read_sensor();
}
