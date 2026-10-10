# Advanced Bare-Metal STM32

A collection of STM32 bare-metal driver development projects.

## Hardware

- MCU: STM32H723ZG
- Board: NUCLEO-H723ZG
- IDE: STM32CubeIDE
- Host OS: Linux

## Projects

| Project | Description |
|---|---|
| `1_gpio_address_config` | Locating Ports and Pins of Periphereas/Components on Nucleo Board, Defining addresses of Modules using Documentation, Creating required registers | 
| `1_gpio_led_stmheader` | Same LED Blinking but used stm32h7xx.h header and data structures of ST |
| `1_gpio_input` | Use Push button as trigger to turn on or off the LEDs |
| `2_uart` | UART TX project that prints a character - verified on Picocom serial terminal |

## Repository Structure

Each numbered directory is an independent STM32CubeIDE project.

```text
Advanced_Baremetal/
├── 1_gpio_addr_config/
├── 2_/
├── 3_/
└── ...

## Development Approach

The projects are developed progressively from low-level peripheral configuration toward more advanced STM32 firmware concepts.

Topics include:

RCC and clock configuration
GPIO
UART/USART
SPI
I2C
ADC
Timers
PWM
Interrupts
DMA
NVIC
RTOS concepts
Advanced STM32H7 peripherals
