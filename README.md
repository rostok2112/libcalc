# libcalc
Simple library with parser of mathematical expressions and operators from string (returns array of tokens with math expressions), translator  to RPN and stack calculator. Also this lib contain simple strtok-like wrapper for calculations

## Tools

GCC and Make
```
sudo apt install build-essential
```
CMake
```
sudo apt install cmake
```

## Depends

Stack lib from: 
```
https://github.com/rostok2112/libstack.git
``` 
Standart **C math lib** 

## Compile

Just run 
```
sh build.sh 
```

## Usage 

Just move **calc.h** from **export/** to **include/** dir and move **libcalc.a** to **lib/** dir of your project
 
Also always link C math lib by **-lm** flag 

Compile example with this lib: 
```
gcc somesource.c -lm -lcalc -L./lib -I./include
```

Examples of usage and docs inside **example/** dir
