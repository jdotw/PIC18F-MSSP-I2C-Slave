
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/i2c1_slave.h"


static void I2C1_ReadCallback() {
    uint8_t buf = SSP1BUF;
}

static void I2C1_WriteCallback() {
    SSP1BUF = 0x0;
}

static void I2C1_AddressCallback() {
    uint8_t buf = SSP1BUF;
}

static void I2C1_WriteColCallback() {
}

static void I2C1_BusColCallback() {
}

void I2C1_Init() {
    I2C1_Open();
    I2C1_SlaveSetBusColIntHandler(I2C1_BusColCallback);
    I2C1_SlaveSetWriteIntHandler(I2C1_WriteCallback);
    I2C1_SlaveSetReadIntHandler(I2C1_ReadCallback);
    I2C1_SlaveSetAddrIntHandler(I2C1_AddressCallback);
    I2C1_SlaveSetWrColIntHandler(I2C1_WriteColCallback);
}
