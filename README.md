# libcalc
Simple library with parser of mathematical expressions and operators from string (returns array of tokens with math expressions), translator  to RPN and stack calculator. Also this lib contain simple strtok-like wrapper for calculations

## Depends

You need  a stack lib from: 
```
https://github.com/rostok2112/libstack.git
``` 
Also you need a standart C math lib 

## Compile

Just run in src/code
```
gcc -c calc.c -o calc.o -I../../include/
ar rc libcalc.a calc.o
```

## Usage 

Just move calc.h from include/ to include/ dir and move libcalc.a to lib/ dir of your project

Compile example with this lib: 
```
gcc somesource.c -lm -lcalc -lstack -L../../lib -I../../include
```
