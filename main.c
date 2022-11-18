/**
 * @file "main.c"
 * @brief Runs as if it was a baremetal approach.
 * @author "Caio Cordeiro"
 */

#include "framework.h"
#include "protocol.h"

int main()
{

    while (TRUE)
    {
        Protocol_Handler();
    }

    return 0;
}
