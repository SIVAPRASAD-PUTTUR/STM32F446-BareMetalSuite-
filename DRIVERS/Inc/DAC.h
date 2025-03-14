#ifndef DAC_DRIVER_H
#define DAC_DRIVER_H

#include <stdint.h>

// DAC Channels
#define DAC_CHANNEL_1 1  // DAC1 Channel 1 (PA4)
#define DAC_CHANNEL_2 2  // DAC1 Channel 2 (PA5)

// Function prototypes
void DAC_Init(void);
void DAC_Enable(uint8_t channel);
void DAC_Disable(uint8_t channel);
void DAC_SetValue(uint8_t channel, uint16_t value);

#endif // DAC_DRIVER_H
