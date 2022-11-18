/**
 * @file "i2c_driver_API.h"
 * @brief Contains all API functions to communicate with I2C bus.
 * @author Caio Cordeiro
 */

#include "framework.h"

/**
 * @brief Setup I2C registers on SERCOM0
 */
void I2c_Init(void);

/**
 * @brief Enables I2C on SERCOM0
 */
void I2c_Enable(void);

/**
 * @brief Reads desired adderess in slave device.
 * 
 * @param[in] address The address that will read.
 * @param[in] size The amount of bits that will be read.
 */
void I2c_ReadData(uint16_t address, uint8_t size);

/**
 * @brief Loads data to I2C buffer to be sent.
 * 
 * @param[in] address The address that will read.
 */
void I2c_WriteData(uint8_t *data, uint16_t address);

/**
 * @brief Gets the data received from I2C bus.
 * 
 * @param[in,out] data The pointer to data array that arrived.
 * @param[out] size The data array size.
 * 
 * @retval EXIT_SUCCESS if data is available
 * @retval EXIT_FAILURE if data is not available
 */
int I2c_GetData(uint8_t *data, uint8_t *size);