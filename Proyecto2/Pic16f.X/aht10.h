#ifndef __aht10_h
#define __aht10_h

#include <stdint.h>

//int AHT10Address = 0x38;
int AHT10Address_Low = 0x38;
int AHT10Address_High = 0x39;

//int HUM_SENSOR_T;
unsigned long aht_readSensor(int GetDataCmd);
//unsigned char AHT10_address;
int aht_begin(unsigned char AHT10_address);
float aht_GetHumidity(void);
float aht_GetTemperature(void);
unsigned char aht_readStatus(void);
void aht_Reset(void);
typedef unsigned char Sensor_CMD;

#endif
