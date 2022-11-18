/**
 * @file "protocol.h"
 * @brief Handles operation between I2C and SPI.
 * @author Caio Cordeiro
 */

#include "framework.h"

/**
 * @brief Performs protocol handling from I2C and SPI.
 */
extern void (*Protocol_Handler)(void);