# Real-Time Fire Detection and Control System using ATmega32 and FreeRTOS

A real-time embedded fire detection and control system built using **ATmega32**, **FreeRTOS**, temperature and smoke sensors, LCD, keypad, LEDs, buzzer, and motor control.

The system continuously monitors temperature and smoke levels, classifies the current condition into operating states, and controls output devices according to the detected state.

---

## Project Description

This project implements a FreeRTOS-based fire detection system with a modular embedded software architecture.

The system reads:

- **LM35 temperature sensor**
- **Analog smoke sensor**

Then it controls:

- **LCD**
- **Keypad**
- **Red LED**
- **Yellow LED**
- **Buzzer**
- **Motor / Fan**

The application uses multiple FreeRTOS tasks to separate sensor reading, state checking, output control, and keypad handling.

---

## Main Features

- Real-time fire detection using FreeRTOS tasks
- Temperature monitoring using LM35 sensor
- Smoke level monitoring using analog smoke sensor
- Mean filtering for sensor readings
- Fire system state machine:
  - `NORMAL`
  - `HEAT`
  - `FIRE`
- LCD display for system state and sensor values
- Keypad password reset in FIRE state
- Buzzer and motor activation during fire alarm
- Red and yellow LED indicators
- ADC synchronization using mutex and binary semaphore
- Modular layered architecture: `LIB`, `MCAL`, `HAL`, `APP`, and `FreeRTOS`

---

## Hardware Components

| Component | Usage |
|---|---|
| ATmega32 | Main microcontroller |
| LM35 | Temperature sensing |
| Analog Smoke Sensor | Smoke detection |
| 16x2 LCD | Display system status and readings |
| 4x4 Keypad | Password input to reset FIRE state |
| Red LED | Fire indication |
| Yellow LED | Heat warning indication |
| Buzzer | Fire alarm |
| Motor / Fan | Fire control output |
| Resistors / wiring | Hardware connections |
| Proteus | Simulation environment |

---

## Software Architecture

The project follows a layered architecture to keep the application separated from direct hardware access.

```text
Project
│
├── LIB
│   ├── StdTypes.h
│   └── MemMap.h
│
├── MCAL
│   ├── DIO
│   │   ├── DIO_Int.h
│   │   ├── DIO_Prg.c
│   │   ├── DIO_Private.h
│   │   ├── DIO_Cfg.h
│   │   └── DIO_Cfg.c
│   │
│   └── ADC
│       ├── ADC_Int.h
│       ├── ADC_Prg.c
│       └── ADC_Private.h
│
├── HAL
│   ├── LCD
│   ├── KeyPad
│   ├── LM35
│   ├── Smoke
│   ├── Motor
│   ├── Buzzer
│   └── LEDs
│
├── APP
│   ├── main.c
│   ├── App_Cfg.h
│   ├── Fire_System.h
│   ├── Fire_System.c
│   ├── Fire_System_Cfg.h
│   ├── Sensor_Tasks.h
│   ├── Sensor_Tasks.c
│   └── Sensor_Tasks_Cfg.h
│
└── FreeRTOS
    ├── FreeRTOS.h
    ├── task.h / tasks.c
    ├── queue.h / queue.c
    ├── semphr.h
    ├── timers.h / timers.c
    └── port files
```

---

## Layer Description

### LIB Layer

Contains common project definitions.

Examples:

- Standard data types
- Common macros
- Error status enum
- ATmega32 memory map
- Register definitions
- Interrupt vector definitions

---

### MCAL Layer

The **Microcontroller Abstraction Layer** provides low-level drivers for ATmega32 peripherals.

Implemented MCAL drivers:

| Driver | Description |
|---|---|
| DIO | Digital input/output pin and port control |
| ADC | Analog-to-digital conversion with blocking, non-blocking, and interrupt support |

---

### HAL Layer

The **Hardware Abstraction Layer** provides drivers for external hardware components.

Implemented HAL drivers:

| Driver | Description |
|---|---|
| LCD | Character LCD display driver |
| KeyPad | 4x4 keypad scanning driver |
| LM35 | Temperature conversion driver |
| Smoke | Smoke percentage conversion driver |
| Motor | Motor ON/OFF control |
| Buzzer | Buzzer ON/OFF control |
| LEDs | Red and yellow LED control |

---

### APP Layer

The application layer contains the system logic and FreeRTOS task creation.

Main application modules:

| Module | Description |
|---|---|
| `main.c` | Initializes drivers and creates FreeRTOS tasks |
| `App_Cfg.h` | Task stack size and priority configuration |
| `Sensor_Tasks` | Reads LM35 and smoke sensor values |
| `Fire_System` | Implements state machine and output control |

---

## System States

The fire system has three main states.

### 1. NORMAL State

The system is in normal condition.

Actions:

- Red LED OFF
- Yellow LED OFF
- Buzzer OFF
- Motor OFF
- LCD displays `NORMAL`
- Temperature is displayed

---

### 2. HEAT State

The system enters HEAT state when high temperature is detected.

Actions:

- Yellow LED ON
- Red LED OFF
- Buzzer OFF
- Motor OFF
- LCD displays `HEAT`
- Temperature and smoke values are displayed

---

### 3. FIRE State

The system enters FIRE state when both heat and smoke conditions indicate fire.

Actions:

- Red LED ON
- Yellow LED OFF
- Buzzer ON
- Motor ON
- LCD displays `FIRE`
- Temperature and smoke values are displayed
- System remains in FIRE state until reset by keypad password

---

## State Machine Logic

The system checks filtered sensor values periodically.

General logic:

```text
If temperature >= 50°C:
    State = HEAT

If temperature is between 45°C and 49°C:
    Stay in HEAT only if the system was already in heat warning condition

If temperature < 45°C:
    State = NORMAL

If State == HEAT and smoke >= 60%:
    State = FIRE

If State == FIRE:
    Stay in FIRE until reset password is entered
```

This provides simple hysteresis behavior to avoid unstable switching around the temperature threshold.

---

## Keypad Reset Logic

When the system is in `FIRE` state, the keypad is used to enter a reset password.

Default password:

```text
1234
```

Clear key:

```text
D
```

If the correct password is entered, the system requests a reset back to `NORMAL`.

---

## FreeRTOS Tasks

| Task | Purpose | Period | Priority |
|---|---|---:|---:|
| `LM35_Task` | Reads and filters LM35 temperature | 500 ms | 4 |
| `Smoke_Task` | Reads and filters smoke sensor | 500 ms | 4 |
| `Fire_System_CheckStateTask` | Updates the fire system state | 200 ms | 3 |
| `Fire_System_MainTask` | Controls LCD, LEDs, buzzer, and motor | 200 ms | 2 |
| `Fire_System_KeypadTask` | Handles keypad password reset | 50 ms | 5 |

Task stack sizes and priorities are configured in:

```text
App_Cfg.h
```

Sensor task timing and filter sample sizes are configured in:

```text
Sensor_Tasks_Cfg.h
```

Fire system timing and password settings are configured in:

```text
Fire_System_Cfg.h
```

---

## ADC Synchronization

Both LM35 and smoke sensors use the ADC peripheral, so access to ADC is protected using FreeRTOS synchronization.

The project uses:

- **Mutex** to protect ADC resource access
- **Binary semaphore** to wait for ADC conversion completion
- **ADC interrupt callback** to release the semaphore from ISR

General flow:

```text
Task takes ADC mutex
Task starts ADC conversion
Task waits on ADC done semaphore
ADC ISR gives semaphore
Task reads ADC result
Task releases ADC mutex
```

This avoids busy waiting inside the sensor tasks and keeps ADC access safe between multiple tasks.

---

## Sensor Filtering

Both LM35 and smoke readings use a simple mean filter.

Default sample size:

```text
10 samples
```

The filter helps smooth sensor noise before the values are used by the fire system state machine.

---

## Important Configuration Values

### Sensor Task Configuration

```c
#define SENSOR_TASK_PERIOD_MS      500u
#define LM35_SAMPLE_SIZE           10u
#define SMOKE_SAMPLE_SIZE          10u
```

### Fire System Configuration

```c
#define CHECK_TASK_PERIOD_MS          200u
#define MAIN_TASK_PERIOD_MS           200u

#define FIRE_PASSWORD_LENGTH          4u
#define FIRE_KEYPAD_TASK_PERIOD_MS    50u

#define FIRE_KEYPAD_CLEAR_KEY         'D'
#define FIRE_KEYPAD_PASSWORD_VALUE    { '1', '2', '3', '4' }
```

### Application Task Configuration

```c
#define KEY_TASK_STACK       100u
#define CHECK_TASK_STACK     120u
#define FIRE_TASK_STACK      150u
#define LM35_TASK_STACK      150u
#define SMOKE_TASK_STACK     150u

#define KEY_TASK_PRIORITY       5u
#define LM35_TASK_PRIORITY      4u
#define SMOKE_TASK_PRIORITY     4u
#define CHECK_TASK_PRIORITY     3u
#define FIRE_TASK_PRIORITY      2u
```

---

## Current Pin Configuration

### LEDs

| Output | Pin |
|---|---|
| Red LED | `DIO_PINC0` |
| Yellow LED | `DIO_PINC1` |

### Buzzer and Motor

| Output | Pin |
|---|---|
| Motor | `DIO_PINC4` |
| Buzzer | `DIO_PINC5` |

### LCD 4-bit Mode

| LCD Pin | MCU Pin |
|---|---|
| RS | `DIO_PINA1` |
| EN | `DIO_PINA2` |
| D4 | `DIO_PINA3` |
| D5 | `DIO_PINA4` |
| D6 | `DIO_PINA5` |
| D7 | `DIO_PINA6` |

### Keypad

| Keypad Part | MCU Pins |
|---|---|
| Rows | `DIO_PINB0` to `DIO_PINB3` |
| Columns | `DIO_PINB4` to `DIO_PINB7` |

### Sensors

| Sensor | ADC Channel |
|---|---|
| LM35 | `CH_0` |
| Smoke Sensor | `CH_7` |

---

## How the Program Starts

The `main.c` file performs the startup sequence:

1. Initialize DIO
2. Initialize LCD
3. Initialize ADC
4. Initialize Keypad
5. Initialize sensor service
6. Initialize fire system module
7. Create FreeRTOS tasks
8. Start FreeRTOS scheduler

Simplified flow:

```c
DIO_Init();
LCD_Init();
ADC_Init(VREF_VCC, ADC_SCALER_64);
KEYPAD_Init();

Sensor_Init();
Fire_System_Init();

xTaskCreate(...);
vTaskStartScheduler();
```

---

## Build Notes

This project is designed for:

- **ATmega32**
- **AVR-GCC / Microchip Studio**
- **FreeRTOS V7 style API**

The project uses FreeRTOS types such as:

```c
xSemaphoreHandle
portTickType
portTICK_RATE_MS
```

---

## Notes

- The LCD driver currently uses blocking delays internally.
- ADC conversion is interrupt-based inside the sensor tasks.
- Smoke readings are only actively used when the fire system is not in `NORMAL` state.
- The system remains latched in `FIRE` state until the correct keypad password is entered.
- The project is suitable for simulation using Proteus.

---

## Author

**Abdelrahman Elzayat**

Embedded Systems / IoT Developer
