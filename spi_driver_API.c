/**
 * @file "spi_driver_API.c"
 * @author Caio Cordeiro
 */

#include "spi_driver_API.h"

/**
 * @brief Setup SPI registers on SERCOM0
 */
void Spi_Init(void)
{
    return;
}

/**
 * @brief Enables SPI on SERCOM0
 */
void Spi_Enable(void)
{
    return;
}

/**
 * @brief Reads desired adderess in slave device.
 * 
 * @param[in] address The address that will read.
 * @param[in] size The amount of bits that will be read.
 */
void Spi_ReadData(uint16_t address, uint8_t size)
{
    return;
}

/**
 * @brief Loads data to SPI buffer to be sent.
 * 
 * @param[in] address The address that will read.
 */
void Spi_WriteData(uint8_t *data, uint16_t address)
{
    return;
}

/**
 * @brief Gets the data received from SPI bus.
 * 
 * @param[in,out] data The pointer to data array that arrived.
 * @param[out] size The data array size.
 * 
 * @retval EXIT_SUCCESS if data is available
 * @retval EXIT_FAILURE if data is not available
 */
int Spi_GetData(uint8_t *data, uint8_t *size)
{
    return EXIT_SUCCESS;
}
