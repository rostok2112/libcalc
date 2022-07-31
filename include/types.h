#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stack.h>

#define ARGUMENT 0
#define INT_DIGIT 1
#define FLOAT_DIGIT 2
#define FUNCTION 3
#define OPERATOR 4
#define OPENING_BRACKET 5
#define CLOSING_BRACKET 6

#define NO_PRIO -1
#define LOWEST_PRIO 0
#define AVARAGE_PRIO 1
#define HIGH_PRIO 2
#define HIGHEST_PRIO 3

#define CONTINUE_WITH_CACHE NULL

typedef struct Token {
    char *token;
    int type:4,
        prio:3;
} Token_t;

typedef struct TokenArr {
    Token_t *tokens;
    int capacity;
} TokenArr_t;

TokenArr_t *_strtok(char *);
TokenArr_t *rpnTranslator(TokenArr_t *);
double stackMachine(double, TokenArr_t *);

double calculateFromStr(double, char *);

#endif // TYPES_H_INCLUDED
