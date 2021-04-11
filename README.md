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



How application 1 (Temprature) works?

First you have to generate code using CubeMX with the configuration stated above. Then, use the code provided in the file
"Temprature_Keil_main.c " as the "main.c" file and the code provided in the file " Temprature_Keil_IRQ_handler.c " as the
"stm3214xx_it.c" file. Afterwards, build the code and load it on the Nuceleoboard. Connect the board in the way shown in
the video (link provided below). Launch Teraterm and set the baud rate to 115200.Connect the TTL to the
laptop (connections shown in the video). Lastly, press the reset button on the chip, open Teraterm and enter the threshold
temprature (must be 2 numbers, i.e: 20,11,07...etc.). The LED will flash if the temprature is higher than the threshold.
The temprature read will be displayed on the Teraterm terminal every 30 seconds.


How application 2 (Parking Sensor)works?

First you have to generate code using CubeMX with the configuration stated above. Then, use the code provided in the file
"Ultrasound_Keil_main.c " as the "main.c" file and the code provided in the file "Ultrasound_Keil_delay_decrement.c " as the
"stm3214xx_it.c" file. In addition, add the files "hcSR04.h" and "hcSR04.c" to the keil project. Afterwards, build the code and load
it on the Nuceleoboard. Connect the board in the way shown in the video (link provided below). Lastly, press the reset button on the chip.
Put an object infront of the sensor; you will hear the buzzer buzzing at an increased frequency, the close the object gets
to the sensor.



