# libcalc
Simple library with parser of mathematical expressions and operators from string (returns array of tokens with math expressions), translator  to RPN and stack calculator. Also this lib contain simple strtok-like wrapper for calculations

## Depends

You need to compile a stack lib from: 
```
https://github.com/rostok2112/libstack.git
```
Just link compiled lib to linker and move header of lib (stack.h) to include/ and static lib to lib/

## Compile

Just run in src/code
```
gcc -c calc.c -o calc.o -L../../lib/ -lstack -I../../include/
ar rc libcalc.a calc.o
```

## Usage 

Just include calc.h from include/ and link  libcalc.a

