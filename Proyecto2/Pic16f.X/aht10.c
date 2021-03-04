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

Sensor_CMD eSensorCalibrateCmd[3] = {0xE1,0x08,0x00};/*inicializacion del comando*//*i2c address + write*/
Sensor_CMD eSensorNormalCmd[3] = {0xA8, 0x00,0x00};
Sensor_CMD eSensorMeasureCmd[3] = {0xAC,0x33,0x00};/*trigger measurement*//*DATA0*/
Sensor_CMD eSensorResetCmd = 0xBA;/*soft reset*/
int GetRHumidityCmd = 1; //true = 1
int GetTempCmd = 0; //false = 0
unsigned char AHT10_address = 0x38;

//**************************************************
//Funciones Globales
//**************************************************

int aht_begin(unsigned char _AHT10_address){
    AHT10_address = _AHT10_address;
    I2C_Master_Init(AHT10_address);
    I2C_Master_Start();
    I2C_Master_Write(eSensorCalibrateCmd[2]);
    I2C_Master_Stop();
    __delay_ms(500);
    if((aht_readStatus()&0x68) == 0x08)
        return 1;
    else
    {
        return 0;
    }
}

/**********************************************************
 * GetHumidity
 *  Gets the current humidity from the sensor.
 *
 * @return float - The relative humidity in %RH
 **********************************************************/
float aht_GetHumidity(void)
{
    float value = aht_readSensor(GetRHumidityCmd);
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
float aht_GetTemperature(void)
{
    float value = aht_readSensor(GetTempCmd);
    return ((200 * value) / 1048576) - 50;
}

/******************************************************************************
 * Private Functions
 ******************************************************************************/

unsigned long aht_readSensor(int GetDataCmd)
{
    unsigned long result, temp[6];

    I2C_Master_Start();
    I2C_Master_Write(eSensorMeasureCmd[2]);
    I2C_Master_Stop();
    __delay_ms(100);

    I2C_Master_Start();

    for(unsigned char i = 0; I2C_Master_Read(1) > 0; i++)
    {
        temp[i] = I2C_Master_Read(1);
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

unsigned char aht_readStatus(void)
{
    unsigned char result = 0;

    I2C_Master_Start();
    result = I2C_Master_Read(1);
    return result;
}

void aht_Reset(void)
{
    I2C_Master_Start();
    I2C_Master_Write(eSensorResetCmd);
    I2C_Master_Stop();
    __delay_ms(20);
}
