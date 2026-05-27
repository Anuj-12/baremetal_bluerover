# Bluerover

A baremetal no-HAL STM32F401RE focused on building a rover from ground up by building custom drivers.
- Modular embedded architecture
- Interrupt driven UART communication
- Blutooth command handling
- PWM motor control

This project is primarly a learning platform for:
- Building embedded architecture 
- Interrupt driven design
- Buffering communication data

## Hardware Used

- STM32F401RE Nucleo Board
- L298N Motor Driver
- HC05 Bluetooth Module

--- For Debugging --- 
- USB to TTL converter
- 8 Channel Logic Analyzer


## Current Features

- GPIO abstraction
- UART drivers
- Interrupt-driven UART RX
- Ring buffer based UART reception
- Parser-based command handling
- PWM motor control
- SysTick based blocking and non-blocking delay
- Modular multi-file structure
- HC05 Bluetooth integration 


## Architecture 

```text
     HC05
      |
      v
 USART1 RX ISR
      |
      v
  Ring Buffer
      |
      v
Superloop Polling
      |
      v
  Line Parser
      |
      v
 Command Decoder
      |
      v
Motor Control Logic
      |
      v
   PWM Timers
```


