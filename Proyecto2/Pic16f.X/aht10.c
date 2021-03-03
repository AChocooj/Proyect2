/*
 * File:   aht10.c
 * Author: Allison Chocooj 
 * me basare en una libreria de arduino como referencia porque no hay mucha 
 * informacion con la que pueda trabajar concretamente
 * Created on 28 de febrero de 2021, 10:42 PM
 */


#include <xc.h>
#include <stdint.h>
#include <math.h>
#include "I2C.h"
#include "aht10.h"

#define WATER_VAPOR 17.62f
#define BAROMETRIC_PRESSURE 243.5f

Sensor_CMD eSensorCalibrateCmd[3] = {0xE1/*inicializacion del comando*/, 0x08/*i2c address + write*/, 0x00};
Sensor_CMD eSensorNormalCmd[3] = {0xA8, 0x00, 0x00};
Sensor_CMD eSensorMeasureCmd[3] = {0xAC,/*trigger measurement*/ 0x33,/*DATA0*/ 0x00};
Sensor_CMD eSensorResetCmd = 0xBA;/*soft reset*/
boolean GetRHumidityCmd = 1; //true = 1
boolean GetTempCmd = 0; //false = 0

//**************************************************
//Funciones Globales
//**************************************************
AHT10Class_AHT10Class(){
}

boolean AHTClass_begin(unsigned char _AHT10_address){
    AHT10_address = _AHT10_address;
    Serial.begin(9600);
    //Serial.println("\x54\x68\x69\x6E\x61\x72\x79\x20\x45\x6C\x65\x74\x72\x6F\x6E\x69\x63\x20\x41\x48\x54\x31\x30\x20\x4D\x6F\x64\x75\x6C\x65\x2E");
    I2C_Master_Init(AHT10_address);
    I2C_Master_Start(AHT10_address);
    I2C_Master_Write(eSensorCalibrateCmd, 3);
    I2C_Master_Stop();
    //Serial.println("https://thinaryelectronic.aliexpress.com");
    __delay:ms(500);
    if((readStatus()&0x68) == 0x08)
        return true;
    else
    {
        return false;
    }
}

/**********************************************************
 * GetHumidity
 *  Gets the current humidity from the sensor.
 *
 * @return float - The relative humidity in %RH
 **********************************************************/
float AHT10Class_GetHumidity(void)
{
    float value = readSensor(GetRHumidityCmd);
    if (value == 0) {
        return 0;                       // Some unrealistic value
    }
    return value * 100 / 1048576;
}

/**********************************************************
 * GetTemperature
 *  Gets the current temperature from the sensor.
 *
 * @return float - The temperature in Deg C
 **********************************************************/
float AHT10Class_GetTemperature(void)
{
    float value = readSensor(GetTempCmd);
    return ((200 * value) / 1048576) - 50;
}

/******************************************************************************
 * Private Functions
 ******************************************************************************/

unsigned long AHT10Class_readSensor(boolean GetDataCmd)
{
    unsigned long result, temp[6];

    I2C_Master_Start(AHT10_address);
    I2C_Master_Write(eSensorMeasureCmd, 3);
    I2C_Master_Stop();
    __delay_ms(100);

    I2C_Master_Start(AHT10_address, 6);

    for(unsigned char i = 0; I2C_Master_Start() > 0; i++)
    {
        temp[i] = I2C_Master_Read();
    }   

    if(GetDataCmd)
    {
        result = ((temp[1] << 16) | (temp[2] << 8) | temp[3]) >> 4;
    }
    else
    {
        result = ((temp[3] & 0x0F) << 16) | (temp[4] << 8) | temp[5];
    }

    return result;
}

unsigned char AHT10Class_readStatus(void)
{
    unsigned char result = 0;

    I2C_Master_Start(AHT10_address, 1);
    result = I2C_Master_Read();
    return result;
}

void AHT10Class_reset(void)
{
    I2C_Master_Start(AHT10_address);
    I2C_Master_Write(eSensorResetCmd);
    I2C_Master_Stop();
    __delay_ms(20);
}
