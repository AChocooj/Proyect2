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
boolean GetRHumidityCmd = 1; //true = 1
boolean GetTempCmd = 0; //false = 0

//**************************************************
//Funciones Globales
//**************************************************
AHT10Class::AHT10Class(){
}

boolean AHTClass::begin(unsigned char _AHT10_address){
    
    
    
}

void main(void) {
    return;
}
