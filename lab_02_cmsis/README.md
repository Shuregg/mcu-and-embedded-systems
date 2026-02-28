# Lab 2. CMSIS and LED blinking

## 1. GPIO intro

| Регистр       | Тип регистра | Назначение                        | Варианты конфигурации для отдельного вывода                          |
| ------------- | ------------ | --------------------------------- | -------------------------------------------------------------------- |
| GPIOx_MODER   | Контрольный  | Выбор режима GPIO                 | input, output, AF, analog                                            |
| GPIOx_OTYPER  | Контрольный  | Конфигурирует тип цифрового вывод | «Push Pull» (=0) или «Open Drain» (=1)                               |
| GPIOx_OSPEEDR | Контрольный  | Конфигурация скорости GPIO        | 00: Low speed, 01: Medium speed, 10: High speed, 11: Very high speed |

## 2. Code analysis

### startup.s

#### Reset_Handler function

```assembly
Reset_Handler:
  ldr   sp, =_estack      /* set stack pointer */

/* Call the ExitRun0Mode function to configure the power supply */
  bl  ExitRun0Mode
/* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit
```

* `ldr   sp, =_estack` - assign  `sp` (Stack pointer) register to `_estack` (End of stack) value;

* `bl  ExitRun0Mode` - call function `ExitRun0Mode` с возвращением;
  * `ExitRun0Mode()`: Specifies the Power Supply source. This function is called at startup just after reset and before the call of SystemInit(). This call is made inside the "startup_stm32h7xx.s" file.

* `bl  SystemInit` - call function `SystemInit` and return;
  * SystemInit is the clock system initialization function.

* `ldr r0, =_sdata` - ;

* `ldr r1, =_edata` - assign `r1` register to start address of data section in RAM (VMA);

* `ldr r2, =_sidata` - assign `r2` register to start address of data section in FLASH (LMA);

* `movs r3, #0` - Write 0 to r3;

* `b LoopCopyDataInit` - Branching to function `LoopCopyDataInit`;
  * This function copies initialized data from FLASH to RAM.
  * This function allocates memory for not initialized data in RAM.

### system.c

### STM32H7xx.h

* Macros:
  * `__cplusplus`

  * `STM32H745xx`

    ```c
    #elif defined(STM32H745xx)
      #include "stm32h745xx.h"
    #elif
    //...
    ```

## 3. Building, firmware uploading and program debugging

```bash
pio run 

```

```bash
Processing hello_led (platform: ststm32; board: nucleo_h745zi_q; framework: cmsis)
---------------------------------------------------------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/ststm32/nucleo_h745zi_q.html
PLATFORM: ST STM32 (19.4.0) > ST Nucleo H745ZI-Q
HARDWARE: STM32H745ZIT6 480MHz, 512KB RAM, 1MB Flash
DEBUG: Current (stlink) On-board (stlink) External (blackmagic, cmsis-dap, jlink)
PACKAGES: 
 - framework-cmsis @ 2.50501.200527 (5.5.1) 
 - framework-cmsis-stm32h7 @ 1.10.6 
 - tool-ldscripts-ststm32 @ 0.2.0 
 - toolchain-gccarmnoneeabi @ 1.70201.0 (7.2.1)
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 1 compatible libraries
Scanning dependencies...
Dependency Graph
|-- myled
Building in debug mode
Compiling .pio/build/hello_led/system/startup.o
Compiling .pio/build/hello_led/system/system.o
Compiling .pio/build/hello_led/src/hello_led.o
Compiling .pio/build/hello_led/lib728/myled/myled.o
Archiving .pio/build/hello_led/lib728/libmyled.a
Indexing .pio/build/hello_led/lib728/libmyled.a
Linking .pio/build/hello_led/firmware.elf
Checking size .pio/build/hello_led/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [          ]   0.0% (used 32 bytes from 524288 bytes)
Flash: [          ]   0.1% (used 644 bytes from 1048576 bytes)
Building .pio/build/hello_led/firmware.bin
```

Usage of "`broken_path`" allows us to use and compile custom `system.c` and `startup.s` files without conflicts.

## 4. Bidirectional semihosting lib (vterm)

```bash
pio device monitor -e hello_led
```

```bash
--- Terminal on /dev/ttyACM0 | 115200 8-N-1
--- Available filters and text transformations: debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
--- More details at https://bit.ly/pio-monitor-filters
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
Led was toggled  11 time(s)
```

## 5.On-chip unit testing

```bash
pio test -e hello_led
```

```bash
Verbosity level can be increased via `-v, -vv, or -vvv` option
Collected 1 tests

Processing target/test_myled in hello_led environment
------------------------------------------------------------------------------------------------------------------------------------------------
Building & Uploading...
xPack Open On-Chip Debugger 0.12.0-01004-g9ea7f3d64-dirty (2023-01-30-15:03)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
debug_level: 1

Warning : could not use CTI with a single core device, CTI is disabled
srst_only separate srst_nogate srst_open_drain connect_deassert_srst

[stm32h7x.cpu0] halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x08000380 msp: 0x20020000
** Programming Started **
Warn : Adding extra erase range, 0x08001920 .. 0x0801ffff
** Programming Finished **
** Verify Started **
** Verified OK **
** Resetting Target **
shutdown command invoked
Testing...
If you don't see any output for the first 10 secs, please reset board (press reset button)

test/target/test_myled/myled_toggle.c:25: test_myled_toggle     [PASSED]
------------------------------------------- hello_led:target/test_myled [PASSED] Took 12.70 seconds -------------------------------------------

=================================================================== SUMMARY ===================================================================
Environment    Test               Status    Duration
-------------  -----------------  --------  ------------
hello_led      target/test_myled  PASSED    00:00:12.700
================================================== 1 test cases: 1 succeeded in 00:00:12.700 ==================================================
```

## Q&A

HSE = 25000000 Hz