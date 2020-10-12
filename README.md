# Build using [Scons][1]

[1]: http://scons.org/ "Scons"


## To build target image
At the project root do:
```
$ mkdir build && cd build
$ cmake -G"Ninja" -DCMAKE_TOOLCHAIN_FILE:PATH="..\arm-none-eabi-gcc.cmake"  ..
```
This generates a `ninja` build file. Now do:
```
$ cmake --build .
```
or
```
$ ninja
```

This will generate a file ```feabhas-stm32f407.elf```


## To run the image on Qemu

```
$ ../qemu-scripts/run_leds.sh feabhas-stm32f407.elf
```

## To clean the build
```
$ ninja clean
```

## To build with the RTOS enabled
At the project root do:
```
TBD
```

