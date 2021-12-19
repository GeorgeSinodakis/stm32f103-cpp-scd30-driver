#include "delay.h"
#include "i2c.h"
#include "math.h"

// The default I2C address for the SCD30 is 0x61.
#define SCD30_ADDRESS 0xC2

// Available commands

#define COMMAND_CONTINUOUS_MEASUREMENT 0x0010
#define COMMAND_SET_MEASUREMENT_INTERVAL 0x4600
#define COMMAND_GET_DATA_READY 0x0202
#define COMMAND_READ_MEASUREMENT 0x0300
#define COMMAND_AUTOMATIC_SELF_CALIBRATION 0x5306
#define COMMAND_SET_FORCED_RECALIBRATION_FACTOR 0x5204
#define COMMAND_SET_TEMPERATURE_OFFSET 0x5403
#define COMMAND_SET_ALTITUDE_COMPENSATION 0x5102
#define COMMAND_RESET 0xD304 // Soft reset
#define COMMAND_STOP_MEAS 0x0104
#define COMMAND_READ_FW_VER 0xD100

class scd30
{
public:
    uint8_t crc;
    float co2;
    float humidity;
    float temperature;
    uint8_t data[18];

public:
    scd30(void)
    {
        I2C1_Init();
    }
    // high layer functions
    void triggerContinuousMeasurement(uint16_t mBar)
    {
        sendCMD(COMMAND_CONTINUOUS_MEASUREMENT, mBar);
    }

    void stopContinuousMeasurement()
    {
        sendCMD(COMMAND_STOP_MEAS);
    }

    void setMeasurementInterval(uint8_t seconds)
    {
        sendCMD(COMMAND_SET_MEASUREMENT_INTERVAL, seconds);
    }

    uint16_t getMeasurementInterval(void)
    {
        sendCMD(COMMAND_SET_MEASUREMENT_INTERVAL);
        ms(4);
        readBytes(data, 3);

        return data[0] << 8 | data[1];
    }

    uint8_t getDataReadyStatus()
    {
        sendCMD(COMMAND_GET_DATA_READY);
        ms(4);
        readBytes(data, 3);

        return data[1];
    }

    void readMeasurement(void)
    {
        sendCMD(COMMAND_READ_MEASUREMENT);
        ms(4);
        readBytes(data, 18);

        *((uint8_t *)(&co2) + 0) = data[4];
        *((uint8_t *)(&co2) + 1) = data[3];
        *((uint8_t *)(&co2) + 2) = data[1];
        *((uint8_t *)(&co2) + 3) = data[0];

        *((uint8_t *)(&temperature) + 0) = data[10];
        *((uint8_t *)(&temperature) + 1) = data[9];
        *((uint8_t *)(&temperature) + 2) = data[7];
        *((uint8_t *)(&temperature) + 3) = data[6];

        *((uint8_t *)(&humidity) + 0) = data[16];
        *((uint8_t *)(&humidity) + 1) = data[15];
        *((uint8_t *)(&humidity) + 2) = data[13];
        *((uint8_t *)(&humidity) + 3) = data[12];
    }

    void AutomaticSelfCalibration(bool enable)
    {
        if (enable)
            sendCMD(COMMAND_AUTOMATIC_SELF_CALIBRATION, 1);
        else
            sendCMD(COMMAND_AUTOMATIC_SELF_CALIBRATION, 0);
    }

    uint8_t getAutomaticSelfCalibrationStatus(void)
    {
        sendCMD(COMMAND_AUTOMATIC_SELF_CALIBRATION);
        ms(4);
        readBytes(data, 3);
        return data[1];
    }

    void setForcedRecalibrationValue(uint16_t value)
    {
        sendCMD(COMMAND_SET_FORCED_RECALIBRATION_FACTOR, value);
    }

    uint16_t getForcedRecalibrationValue(void)
    {
        sendCMD(COMMAND_SET_FORCED_RECALIBRATION_FACTOR);
        ms(4);
        readBytes(data, 3);
        return data[0] << 8 | data[1];
    }

    void setTemperatureOffset(uint16_t tempOffset)
    {
        sendCMD(COMMAND_SET_TEMPERATURE_OFFSET, tempOffset);
    }

    uint16_t getTemperatureOffset(void)
    {
        sendCMD(COMMAND_SET_TEMPERATURE_OFFSET);
        ms(4);
        readBytes(data, 3);
        return data[0] << 8 | data[1];
    }

    void setAltitudeCompensation(uint16_t meters)
    {
        sendCMD(COMMAND_SET_ALTITUDE_COMPENSATION, meters);
    }

    uint16_t getAltitudeCompensation(void)
    {
        sendCMD(COMMAND_SET_ALTITUDE_COMPENSATION);
        ms(4);
        readBytes(data, 3);
        return data[0] << 8 | data[1];
    }

    uint16_t readfirmwareversion(void)
    {
        sendCMD(COMMAND_READ_FW_VER);
        ms(4);
        readBytes(data, 3);
        return data[0] << 8 | data[1];
    }

    void softReset(void)
    {
        sendCMD(COMMAND_RESET);
    }

    // low layer functions
    void sendCMD(uint16_t command, uint16_t arg)
    {
        resetCRC();
        I2C1_Start();
        I2C1_Send_Address(SCD30_ADDRESS, I2C_write);
        I2C1_Send_Data((command >> 8 & 0xff));
        I2C1_Send_Data(command & 0xff);
        I2C1_Send_Data((arg >> 8 & 0xff));
        computeCRC((arg >> 8 & 0xff));
        I2C1_Send_Data(arg & 0xff);
        computeCRC(arg & 0xff);
        I2C1_Send_Data(crc);
        I2C1_Stop();
    }

    void sendCMD(uint16_t command)
    {
        I2C1_Start();
        I2C1_Send_Address(SCD30_ADDRESS, I2C_write);
        I2C1_Send_Data((command >> 8 & 0xff));
        I2C1_Send_Data(command & 0xff);
        I2C1_Stop();
    }

    void readBytes(uint8_t *buffer, uint8_t len)
    {
        I2C1_Start();
        I2C1_Send_Address(SCD30_ADDRESS, I2C_read);
        for (uint8_t i = 0; i < len; i++)
        {
            buffer[i] = I2C1_Receive_Data(true);
        }
        I2C1_Stop();
    }

    bool readWord(uint16_t *word)
    {
        uint8_t low, high, sensorCRC;
        resetCRC();
        high = I2C1_Receive_Data(true);
        low = I2C1_Receive_Data(true);
        sensorCRC = I2C1_Receive_Data(true);

        computeCRC(high);
        computeCRC(low);
        if (crc == sensorCRC)
        {
            *word = (high << 8) | low;
            return 0;
        }
        return 1;
    }

    void resetCRC(void)
    {
        crc = 0xff;
    }

    void computeCRC(uint8_t input)
    {
        crc ^= input; // XOR-in the next input byte

        for (uint8_t i = 0; i < 8; i++)
        {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
};