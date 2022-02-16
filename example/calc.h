#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#define CONTINUE_WITH_CACHE NULL
#define FREE_CACHE (char []){-1}

typedef struct Token Token_t;
typedef struct TokenArr TokenArr_t;

TokenArr_t *_strtok(char *inputStr);
TokenArr_t *rpnTranslator(TokenArr_t *inputTokenArr);
double stackMachine(double x, TokenArr_t *expressionArr);

double calculateFromStr(double x, char *strWithExpression);

#endif // CALC_H_INCLUDED