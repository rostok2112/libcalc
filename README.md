<h1 align="center">
  libcalc
</h1>
<h4 align="center">
  Simple library with parser of mathematical expressions and operators from string (returns array of tokens with math expressions), translator  to RPN and stack calculator. Also this lib contain simple strtok-like wrapper for calculations
</h4>
<p align="center">
  <a href="https://github.com/rostok2112/libcalc/blob/main/LICENSE"><img alt="GitHub license" src="https://img.shields.io/github/license/rostok2112/libcalc.svg">
  </a>
</p>

## Tools

GCC and Make
```
sudo apt install build-essential
```
CMake
```
sudo apt install cmake
```
... Or install this tools by yourself

## Depends

Stack lib from: 
```
https://github.com/rostok2112/libstack.git
``` 
Standart **C math lib** 

## Build

Just run 
```
sh build.sh 
```
Or
```
./build.sh
```
If you need specific type of lib like shared, just run
```
sh build.sh SHARED
``` 
Or start build.sh by any another way

## Usage 

Just move **calc.h** from **export/** to **include/** dir and move **libcalc.a** to **lib/** dir of your project
 
Also always link C math lib by **-lm** flag 

Compile example with this lib: 
```
gcc somesource.c -lm -lcalc -L./lib -I./include
```

Examples of usage and docs inside **example/** dir
