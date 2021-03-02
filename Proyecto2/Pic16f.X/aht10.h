#ifndef __aht10_h
#define __aht10_h

#include <stdint.h>

typedef enum {
    eAHT10Address_default = 0x38,
            eAHT10Address_Low = 0x38,
            eAHT10Address_High = 0x39,
}
HUM_SENSOR_T;

typedef unsigned char Sensor_CMD;

class AHT10Class {
private:
    unsigned long readSensor(boolean GetDataCmd);
    unsigned char AHT10_address;
public:
    AHT10Class();
    boolean begin(unsigned char _AHT10_address = eAHT10Address_default);
};