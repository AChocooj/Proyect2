/*
 * File:   aht10.c
 * Author: quema
 *
 * Created on 28 de febrero de 2021, 10:42 PM
 */


#include <xc.h>
#include <stdint.h>
#include <math.h>
//#include <Arduino.h>
//#include <Wire.h>
#include "Thinary_AHT10.h"

#define WATER_VAPOR 17.62f
#define BAROMETRIC_PRESSURE 243.5f

Sensor_CMD eSensorCalibrateCmd[3] = {0xE1, 0x08, 0x00};
Sensor_CMD eSensorNormalCmd[3] = {0xA8, 0x00, 0x00};
Sensor_CMD eSensorMeasureCmd[3] = {0xAC, 0x33, 0x00};
Sensor_CMD eSensorResetCmd = 0xBA;
boolean GetRHumidityCmd = true; //true = 1
boolean GetTempCmd = false; //false = 0

//**************************************************
//Funciones Globales
//**************************************************
AHT10Class::AHT10Class(){
}

boolean AHTClass::begin(unsigned char _AHT10_address){
    AHT10_address = _AHT10_address;
    Serial.begin(9600);
    Serial.println("\x54\x68\x69\x6E\x61\x72\x79\x20\x45\x6C\x65\x74\x72\x6F\x6E\x69\x63\x20\x41\x48\x54\x31\x30\x20\x4D\x6F\x64\x75\x6C\x65\x2E");
    Wire.begin(AHT10_address);
    Wire.beginTransmission(AHT10_address);
    Wire.write(eSensorCalibrateCmd, 3);
    Wire.endTransmission();
    Serial.println("https://thinaryelectronic.aliexpress.com");
    delay(500);
    if((readStatus()&0x68) == 0x08)
        return true;
    else
    {
        return false;
    }
}

void main(void) {
    return;
}
