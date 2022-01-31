#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct Token{
    char *token;
    int type:4,
        prio:3;
} Token_t;

typedef struct TokenArr{
    Token_t *tokens;
    int capacity;
} TokenArr_t;

typedef union Cast {
    double d;
    long long int li;
    float f;
    int i;
    short s;
    char c
} Cast_t;

TokenArr_t *_strtok(char *);
TokenArr_t *rpnTranslator(TokenArr_t *);
double stackMachine(double, TokenArr_t *);

double calculateFromStr(double, char *);

#endif // TYPES_H_INCLUDED
