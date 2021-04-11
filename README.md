# Embedded-Project-1
Cooperative Scheduler for Embedded Systems

CubeMX for First Application (Read Temp from sensor, capture threshold from TeraTerm, blink LED accordingly)
To set up the cubeMX configurations for the first application, follow the following steps:
*We are using UART1 thus we will need to use a USB-TTL to be able to read from the TeraTerm*

I2C
Set the I2C configuration of the Nucleo-32 board to I2C from the dropdown menu. This will allow to receive data from the sensor and send the clock to it.

NVIC
Set the preemption priority of the UART1 handler to 7 and enable it.

RCC
Set the RCC to crystal/ceramic oscillator
SYS
Set the debug mode to Serial wire.

USART1
Set the UART1 to Asynchronous mode to allow communication between the teraterm and the Nucleo-32 board. 


CubeMX for the Second Application (Get distance using ultrasonic sensor then turn on buzzer and change its buzzing frequency accordingly)
To set up the cubeMX configurations for the first application, follow the following steps:

TIM1
Set the clock source to Internal Clock.
Set channel1 to Input capture direct mode
In the NVIC settings, enable the TIM1 capture compare interrupt.

NVIC
Enable the TIM1 capture compare interrupt.

In the Pin Layout, set pin PA4 as GPIO_Output.
