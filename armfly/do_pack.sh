#!/bin/bash

make -C Project/GCC/ -j12

#./tools/toolchain/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-nm -A -S --size-sort build/app.elf 