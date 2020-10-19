#!/bin/bash
arm-none-eabi-gcc --specs=rdimon.specs -lgcc -lc -lm -lrdimon testarm.c -o testarm
qemu-arm-static ./testarm