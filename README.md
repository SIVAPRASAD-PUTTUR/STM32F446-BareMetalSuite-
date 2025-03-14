Overview
The STM32F446 BareMetalSuite is a comprehensive library for managing low-level drivers and peripherals on the STM32F446ZE microcontroller, without reliance on HAL libraries. It aims to provide developers with robust, efficient, and customizable bare-metal drivers for embedded systems.

Features
GPIO Driver:

Configurable input, output, alternate functions, and analog modes.

Easy-to-use pin manipulation functions like read, write, toggle, and more.

I2C Driver:

Bare-metal I2C communication interface with support for multiple instances.

Customizable initialization for GPIO-based I2C pins.

Functions for reading, writing, and managing ACK signals.

DAC Driver:

Management of multiple DAC channels.

Bare-metal initialization for precision analog output.

Flexible control of DAC output values (12-bit resolution).

Scalability:

Designed to integrate additional peripherals (e.g., SPI, ADC, USART).

Project Structure
STM32F446-BareMetalSuite/
├── inc/
│   ├── GPIO.h        # GPIO driver header
│   ├── i2c_driver.h  # I2C driver header
│   ├── dac_driver.h  # DAC driver header
├── src/
│   ├── GPIO.c        # GPIO driver implementation
│   ├── i2c_driver.c  # I2C driver implementation
│   ├── dac_driver.c  # DAC driver implementation
├── README.md         # Project documentation (this file)
└── main.c            # Example usage and testing
Requirements
Hardware: STM32F446ZE microcontroller.

Software: STM32CubeIDE or any preferred ARM GCC-based toolchain.

Getting Started
Clone the repository:

bash
git clone https://github.com/SIVAPRASAD-PUTTUR/STM32F446-BareMetalSuite-.git
Open the project in your STM32 development environment.

Include the driver headers (GPIO.h, i2c_driver.h, dac_driver.h) in your application.

Write your application logic using the provided drivers.

Usage Example
Initializing I2C with GPIO
c
#include "GPIO.h"
#include "i2c_driver.h"

int main(void) {
    // Initialize GPIO for I2C
    setPin(PB, 6, AF);   // I2C SCL on PB6
    setPin(PB, 7, AF);   // I2C SDA on PB7

    // Initialize I2C1
    I2C_Init(I2C_INSTANCE_1, PB, 6, PB, 7, 16000000);

    // Write data to a device
    I2C_Start(I2C_INSTANCE_1);
    I2C_Write(I2C_INSTANCE_1, 0x78, 0x55); // Send data
    I2C_Stop(I2C_INSTANCE_1);

    while (1);
}
Setting DAC Values
c
#include "dac_driver.h"

int main(void) {
    // Initialize DAC
    DAC_Init();
    DAC_Enable(DAC_CHANNEL_1);

    // Set DAC output to midpoint
    DAC_SetValue(DAC_CHANNEL_1, 2048);

    while (1);
}
Contribution
Contributions are welcome! Feel free to:

Report issues

Suggest new features

Submit pull requests

License
This project is open-source and distributed under the MIT License. See the LICENSE file for more details.

Author
SIVAPRASAD PUTTUR Embedded Systems Developer passionate about bare-metal programming and low-level drivers.
