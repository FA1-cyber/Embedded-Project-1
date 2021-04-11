# Embedded-Project-1
Cooperative Scheduler for Embedded Systems

**CubeMX for First Application (Read Temp from sensor, capture threshold from TeraTerm, blink LED accordingly)**
To set up the cubeMX configurations for the first application, follow the following steps:
*We are using UART1 thus we will need to use a USB-TTL to be able to read from the TeraTerm*

- I2C
  Set the I2C configuration of the Nucleo-32 board to I2C from the dropdown menu. This will allow to receive data from the sensor and send the clock to it.

- NVIC
  Set the preemption priority of the UART1 handler to 7 and enable it.

- RCC
  Set the RCC to crystal/ceramic oscillator
  
- SYS
  Set the debug mode to Serial wire.

- USART1
  Set the UART1 to Asynchronous mode to allow communication between the teraterm and the Nucleo-32 board. 


**CubeMX for the Second Application (Get distance using ultrasonic sensor then turn on buzzer and change its buzzing frequency accordingly)**
To set up the cubeMX configurations for the first application, follow the following steps:

- TIM1
  Set the clock source to Internal Clock.
  Set channel1 to Input capture direct mode
  In the NVIC settings, enable the TIM1 capture compare interrupt.

- NVIC
  Enable the TIM1 capture compare interrupt.

- In the Pin Layout, set pin PA4 as GPIO_Output.



**How application 1 (Temprature) works?**

  First you have to generate code using CubeMX with the configuration stated above. Then, use the code provided in the file
"Temprature_Keil_main.c " as the "main.c" file and the code provided in the file " Temprature_Keil_IRQ_handler.c " as the
"stm3214xx_it.c" file. Afterwards, build the code and load it on the Nuceleoboard. Connect the board in the way shown in
the video (link provided below). Launch Teraterm and set the baud rate to 115200.Connect the TTL to the
laptop (connections shown in the video). Lastly, press the reset button on the chip, open Teraterm and enter the threshold
temprature (must be 2 numbers, i.e: 20,11,07...etc.). The LED will flash if the temprature is higher than the threshold.
The temprature read will be displayed on the Teraterm terminal every 30 seconds.


**How application 2 (Parking Sensor)works?**

  First you have to generate code using CubeMX with the configuration stated above. Then, use the code provided in the file
"Ultrasound_Keil_main.c " as the "main.c" file and the code provided in the file "Ultrasound_Keil_delay_decrement.c " as the
"stm3214xx_it.c" file. In addition, add the files "hcSR04.h" and "hcSR04.c" to the keil project. Afterwards, build the code and load
it on the Nuceleoboard. Connect the board in the way shown in the video (link provided below). Lastly, press the reset button on the chip.
Put an object infront of the sensor; you will hear the buzzer buzzing at an increased frequency, the close the object gets
to the sensor.


**Code explanation (Application 1):**

  The code can be split into multiple parts. Firstly, we have the UART handler, which is responsible for receiving the threshold temperature from the user through teraterm and storing in a variable to allow accessing by the tasks. Secondly, we have the tasks. We split the process into 3 tasks. The first task (ReadTemp) reads the temperature from the sensor and stores it in a global variable to allow accessing by other tasks. The second task (CheckThreshold) compares the threshold temperature to the received temperature from the sensor and sets a flag “flagToggle” to 1 if the threshold is smaller in value and to 0 if otherwise. Last task (ToggleLED) checks the “flagToggle” and toggles the LED if the flag is set to 1. Furthermore, we have the scheduler itself. Each task is queued into the scheduler queue with a different priority (ReadTemp having the highest priority and ToggleLED having the least priority). The scheduler loops over the tasks in the ready queue and executes them according to their priority. If any task contains a “Rerunme” function, it queues it in the delay queue with the number of ticks passed as a parameter. We fire the systick handler every tick to decrement the delay of each function in the delay queue by 1. And the scheduler loops over the delay queue with every call to the dispatch function and dequeues any function that has the number of ticks equal to 0 and queues it in the ready queue. Since we set each tick to have the value of 50 msec, we need 600 ticks to execute every 30 seconds. This is why we have “ReadTemp” function and the “CheckThreshold” function with a Rerunme(600). However, since we would need the LED to be either continuously flashing or continuously turned off (depending on the comparison) we have it with a Rerunme(1).


**Code explanation (Application 2):**

  The code can be split into multiple parts. Firstly, we have the tasks. We split the process into 3 tasks. The first task (ReadDistance) reads the distance from the sensor and stores it in a global variable to allow accessing by other tasks. The second task (setfrequency) compares the read distance to certain preset thresholds and sets the frequency of the buzzer based on the distance. Last task (toggleBuzzer) toggles the buzzer with the frequency set by the setfrequency functiion. Furthermore, we have the scheduler itself. Each task is queued into the scheduler queue with a different priority (ReadDistance having the highest priority and ToggleBuzzer having the least priority). The scheduler loops over the tasks in the ready queue and executes them according to their priority. If any task contains a “Rerunme” function, it queues it in the delay queue with the number of ticks passed as a parameter. We fire the systick handler every tick to decrement the delay of each function in the delay queue by 1. And the scheduler loops over the delay queue with every call to the dispatch function and dequeues any function that has the number of ticks equal to 0 and queues it in the ready queue. Since we need the distance to be frequently read, we set the rerunme of both the ReadDistance and setfrequency functions to only 10 (reading the distance every half second). However, since we would need the buzzer to be continuously buzzing (with a frequency dependent on the distance) we have it with a Rerunme(1).
  
  
  **Links for videos of the applications:**
1. https://youtu.be/vbnia-J4dXU  -> Temperature Sensor
2. https://youtu.be/SIvq5zDdexQ  -> Parking Sensor

**Test Cases (Timing Diagrams)**
![CamScanner 04-11-2021 19 47_1](https://user-images.githubusercontent.com/58788527/114315355-ea683280-9afe-11eb-969e-c5ed36dc0c75.jpg)

**Test Cases (Screenshots from running the code)**
<img width="735" alt="Screen Shot 2021-04-11 at 7 49 31 PM" src="https://user-images.githubusercontent.com/58788527/114315408-2d2a0a80-9aff-11eb-800c-b31d946a58c5.png">


