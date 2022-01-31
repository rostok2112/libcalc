#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#define CONTINUE_WITH_CACHE NULL
#define FREE_CACHE (char []){-1}

typedef struct Token Token_t;
typedef struct TokenArr TokenArr_t;
typedef union Cast  Cast_t;

TokenArr_t *_strtok(char *);
TokenArr_t *rpnTranslator(TokenArr_t *);
double stackMachine(double, TokenArr_t *);

double calculateFromStr(double, char *);

#endif // CALC_H_INCLUDED
