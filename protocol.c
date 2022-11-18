
#include "protocol.h"
#include "framework.h"
#include "i2c_driver_API.h"
#include "spi_driver_API.h"

typedef enum
{
    PROTOCOL_INIT,
    PROTOCOL_I2C,
    PROTOCOL_SPI,
} protocol_state_t;

static protocol_state_t protocolState = PROTOCOL_INIT;

// Function that initializes the protocol
void Protocol_Initialize(void);

// Function that keeps protocol on I2C
void Protocol_I2C(void);

void Protocol_I2cInit(void);

void Protocol_I2cPoll(void);

void Protocol_I2cReadData(void);

void Protocol_I2cRunning(void);

void Protocol_SPI(void);

void Protocol_SpiInit(void);

void Protocol_SpiPoll(void);

void Protocol_SpiReadData(void);

void Protocol_SpiRunning(void);

// Pointer that points to the protocol current state
void (*Protocol_Handler)(void) = Protocol_Initialize;

// Pointer that points to I2C protocol current state
void (*Protocol_I2cHandler)(void) = Protocol_I2cInit;

// Pointer that points to SPI protocol current state
void (*Protocol_SpiHandler)(void) = Protocol_SpiInit;

/**
 * @brief Initialize protocol itself.
 */
void Protocol_Initialize(void)
{
    // Start as I2C
    Protocol_Handler = Protocol_I2C;
    
    return;
}

/**
 * @brief Initialize I2C interface
 */
void Protocol_I2cInit(void)
{
    // Initialize I2C interface
    I2c_Init();
    I2c_Enable();
    
    // Go to poll state
    Protocol_I2cHandler = Protocol_I2cPoll;
    
    return;
}

/**
 * @brief Performs polling on slave device to check for existance.
 * 
 */
void Protocol_I2cPoll(void)
{
    uint16_t address = 0x10;
    uint8_t size = 3;
    
    // Try to read 3 bits on address 0x10
    I2c_ReadData(address, size);
    
    /*
    //Start a timer here
    
    timer_reset(data_timer);
    
    */
    
    // Go to read data state
    Protocol_I2cHandler = Protocol_I2cReadData;
    
    return;
}

/**
 * @brief Tries to read data on the slave.
 */
void Protocol_I2cReadData(void)
{
    uint8_t *data;
    uint8_t size;
    
    // Look for a timer timeout here. Wait 100ms before checking for data
    /*
    
    if (timer_is_timeout(data_timer) == FALSE)
    {
        return
    }
    
    
    */
    
    // Check if received data
    if (EXIT_SUCCESS == I2c_GetData(data, &size))
    {
        // Device is alive, keep on I2C
        Protocol_I2cHandler = Protocol_I2cRunning;
    }
    else
    {
        
        // Reset I2C next time
        Protocol_I2cHandler = Protocol_I2cInit;
        
        // Go to SPI mode
        Protocol_Handler = Protocol_SPI;
        
    }
    
}

/**
 * @brief Do I2C duties, from time to time send a poll if didn`t communicate in the last
 * 10 seconds.
 */
void Protocol_I2cRunning(void)
{
    return;
}

/**
 * @brief Keeps running I2C protocol.
 */
void Protocol_I2C(void)
{
    
    // Keep running I2C
    Protocol_I2cHandler();
    
    return;
    
}

/**
 * @brief Keeps running SPI protocol
 */
void Protocol_SPI(void)
{
    
    // Keep running SPI protocol
    Protocol_SpiHandler();
    
}

/**
 * @brief Initialize SPI interface.
 */
void Protocol_SpiInit(void)
{
    
    // Initialize SPI bus
    Spi_Init();
    Spi_Enable();
    
    // Go to poll state
    Protocol_SpiHandler = Protocol_SpiPoll;
    
}

void Protocol_SpiPoll(void)
{
    uint16_t address = 0x12;
    uint8_t size = 5;
    
    // Try to read 5 bits on address 0x12
    Spi_ReadData(address, size);
    
    /*
    //Start a timer here
    
    timer_reset(data_timer);
    
    */
    
    // Go to read data state
    Protocol_SpiHandler = Protocol_SpiReadData;
    
    return;
}

void Protocol_SpiReadData(void)
{
    uint8_t *data;
    uint8_t size;
    
    // Look for a timer timeout here. Wait 100ms before checking for data
    /*
    
    if (timer_is_timeout(data_timer) == FALSE)
    {
        return
    }
    
    
    */
    
    // Check if received data
    if (EXIT_SUCCESS == I2c_GetData(data, &size))
    {
        // Device is alive, keep on SPI
        Protocol_SpiHandler = Protocol_SpiRunning;
    }
    else
    {
        
        // Reset SPI next time
        Protocol_SpiHandler = Protocol_SpiInit;
        
        // Go to I2C mode
        Protocol_Handler = Protocol_I2C;
        
    }
}

/**
 * @brief Do SPI duties, from time to time send a poll if didn`t communicate in the last
 * 10 seconds.
 */
void Protocol_SpiRunning(void)
{
    return;
}
