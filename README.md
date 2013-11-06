stm32f3discovery-test
=====================

A test makefile project of stm32f3discovery. 
This project contains LED flashing sample source, makefile, linker script, gdb script and openocd script.

Build and Debug Steps
------

1. Build project
make

2. Run OpenOCD
cd openocd
sudo ./openocd.sh

3. Debug
make debug

Additional  Informations
------

gdb/stm32f3vcdiscovery.script : gdb debugger script which includes flashing commands

ld/stm32f303vc.ld : linker script which is optimized for stm32f303 mpu

openocd/openocd.sh : script which runs OpenOCD (needs root permission)
openocd/stm32f3discovery.cfg : OpenOCD configuration file for STM32F3Discovery
~
~
~
