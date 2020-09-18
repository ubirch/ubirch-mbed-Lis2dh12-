/*!
 * @file
 * @brief Lis2dh12 Accelerometer
 *
 * @author Roxana Meixner
 * @date   2019-06-20
 *
 * @copyright &copy; 2017 ubirch GmbH (https://ubirch.com)
 *
 * ```
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ```
 */

#ifndef UBIRCH_ENERTHING_FIRMWARE_LIS2DH12_H
#define UBIRCH_ENERTHING_FIRMWARE_LIS2DH12_H

#include "mbed.h"
#include "lis2dh12_reg.h"

#define ACC_ARRAYSIZE 32    // size of accelerometer FIFO
#define TEST_ARRAYSIZE 5    // array for sensor self test

typedef struct {
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;
}acceleration_t;

class Lis2dh12
{
public:
    Lis2dh12(I2C *_i2c, lis2dh12_odr_t _sampRate, lis2dh12_fs_t _fullScale, lis2dh12_op_md_t _resolution);

    virtual ~Lis2dh12();

    int16_t init();

    int16_t selfTest();

    int16_t setOperatingMode(lis2dh12_odr_t _sampRate, lis2dh12_fs_t _fullScale, lis2dh12_op_md_t _res);

    int16_t enableSensor();

    int16_t disableSensor();

    int16_t getAccelerationFifo(acceleration_t *accelerationArray, bool debug);

    int16_t enableThsInterrupt(uint16_t thresholdInMg, uint16_t durationInMs);

    int16_t enableFIFOOverflowInterrupt();

    int16_t disableFIFOOverflowInterrupt();

    int16_t resetInterrupt();

private:

    int16_t readReg(uint8_t regAddr, uint8_t *buff, uint16_t buffSize);

    int16_t writeReg(uint8_t regAddr, uint8_t *data, uint16_t len);

    int16_t setDuration(uint16_t userDurationInMs);

    int16_t setThreshold(uint16_t userThresholdInMg);

    int16_t getAcceleration(acceleration_t &acceleration);

    int16_t convert_to_mg(int16_t rawData);

    int16_t resetInterrupt(bool *_xyzHighEvent);

    int16_t checkFifoStatus(bool *_overrun);

    int16_t checkFifoDataLevel();

    int16_t waitForOverrunInt();

    int16_t waitForThresholdInt();

    bool isWaitingForThresholdInterrupt();

    void readAllRegisters(void);

    static uint16_t sampRateToInt(lis2dh12_odr_t sr);

    static uint8_t fullScaleToInt(lis2dh12_fs_t fs);

    static uint8_t resolutionToInt(lis2dh12_op_md_t r);

    I2C *i2c;
    uint8_t i2cAddr;
    lis2dh12_odr_t sampRate;
    lis2dh12_fs_t fullScale;
    lis2dh12_op_md_t resolution;
    bool waitingForThresholdInterrupt;
};

#endif //UBIRCH_ENERTHING_FIRMWARE_LIS2DH12_H
