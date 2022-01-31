#include "../headers/types.h"

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

/*Math expression parser to tokens*/
TokenArr_t *_strtok(char *inputStr)
{
    if(!inputStr)
        return NULL;

    TokenArr_t *tokenArr = malloc(sizeof(TokenArr_t));
    tokenArr->capacity = 0;
    tokenArr->tokens = NULL;
    char buffer [64]  = {'\0'};

    for(int i = 0, j = 0, m = 0;  i < strlen(inputStr); j++, m = 0) {
        tokenArr->tokens = realloc(tokenArr->tokens, ++tokenArr->capacity  * sizeof(Token_t));
m:
        if(isalpha(inputStr[i]))
            if(tolower(inputStr[i]) == 'x' &&
               (
                i  == strlen(inputStr) ||
                !isalpha(inputStr[i + 1])
               )
              )
                tokenArr->tokens[j].type = ARGUMENT, tokenArr->tokens[j].prio = NO_PRIO, buffer[m++] = inputStr[i++];
            else {
                while(isalpha(inputStr[i]))
                    if(m < sizeof(buffer))
                        buffer[m++] = inputStr[i++];
                tokenArr->tokens[j].type = FUNCTION;
                tokenArr->tokens[j].prio = HIGHEST_PRIO;
            }
        else if(isdigit(inputStr[i])) {
            int flag = 0;
            while(
                  isdigit(inputStr[i]) ||
                  inputStr[i] == '.'   ||
                  inputStr[i] == ','
                 ) {
                if(inputStr[i] == '.' || inputStr[i] == ',')
                    flag = 1;
                if(m < sizeof(buffer))
                    buffer[m++] = inputStr[i++];
            }
            tokenArr->tokens[j].prio = NO_PRIO;
            tokenArr->tokens[j].type = flag ? FLOAT_DIGIT : INT_DIGIT;
        } else if(
                  inputStr[i] == '(' ||
                  inputStr[i] == ')' ||
                  inputStr[i] == '-' ||
                  inputStr[i] == '+' ||
                  inputStr[i] == '/' ||
                  inputStr[i] == '*' ||
                  inputStr[i] == '^' ||
                  inputStr[i] == '%'
                 ) {
            tokenArr->tokens[j].prio = NO_PRIO;

            switch(inputStr[i]) {
                case ')':
                    tokenArr->tokens[j].type = CLOSING_BRACKET;
                    break;
                case '(':
                    tokenArr->tokens[j].type = OPENING_BRACKET;
                    break;
                default:
                    tokenArr->tokens[j].type = OPERATOR;
                    switch(inputStr[i]) {
                        case '-':
                            ;
                        case '+':
                            tokenArr->tokens[j].prio = LOWEST_PRIO;
                            break;
                        case '%':
                            ;
                        case '/':
                            ;
                        case '*':
                            tokenArr->tokens[j].prio = AVARAGE_PRIO;
                            break;
                        case '^':
                            tokenArr->tokens[j].prio = HIGH_PRIO;
                            break;
                }
            }
            buffer[m++] = inputStr[i++];
        } else {
            i++;
            goto m;
        }
        buffer[m] = '\0';

        tokenArr->tokens[j].token = calloc(m, sizeof(char));
        strcpy(tokenArr->tokens[j].token, buffer);
        memset(buffer, 0, m);
    }
    return tokenArr;
}

/*Translator from infix to postfix notation (Reverse Poland notation)*/
TokenArr_t *rpnTranslator(TokenArr_t *inputTokenArr)
{
    if(!inputTokenArr)
        return NULL;

    Stack_t *head = NULL;
    TokenArr_t *outputTokenArr = malloc(sizeof(TokenArr_t));
    outputTokenArr->capacity = 0;
    outputTokenArr->tokens = calloc(inputTokenArr->capacity, sizeof(Token_t));

    int cnt = 0; // current  index  of output str
    for(int i = 0; i < inputTokenArr->capacity; i++)
        switch(inputTokenArr->tokens[i].type) {
            case ARGUMENT ... FLOAT_DIGIT:   // argument, int digit, float digit
                outputTokenArr->tokens[cnt++] = inputTokenArr->tokens[i];
                outputTokenArr->capacity++;
                break;
            case FUNCTION:
                ;
            case OPENING_BRACKET:
                stack_push(&head, &inputTokenArr->tokens[i]);
                break;
            case OPERATOR: // + - / * ^ %
                if(
                   !stack_top(head) ||
                   ((Token_t *)stack_top(head))->prio < inputTokenArr->tokens[i].prio ||
                   ((Token_t *)stack_top(head))->type == OPENING_BRACKET
                  )
                    stack_push(&head, &inputTokenArr->tokens[i]);
                else {
                    while(stack_top(head) && ((Token_t *)stack_top(head))->prio >= inputTokenArr->tokens[i].prio)
                        outputTokenArr->tokens[cnt++] = *((Token_t *)stack_pop(&head)), outputTokenArr->capacity++;
                    stack_push(&head, &inputTokenArr->tokens[i]);
                }
                break;
            case CLOSING_BRACKET:
                while(stack_top(head) && ((Token_t *)stack_top(head))->type != OPENING_BRACKET)
                    outputTokenArr->tokens[cnt++] = *((Token_t *)stack_pop(&head)), outputTokenArr->capacity++;
                stack_pop(&head);
                break;
        }

    while(stack_top(head))
        outputTokenArr->tokens[cnt++] = *((Token_t *)stack_pop(&head)), outputTokenArr->capacity++;

    outputTokenArr->tokens = realloc(outputTokenArr->tokens, outputTokenArr->capacity * sizeof(Token_t));
    free(inputTokenArr);

    return outputTokenArr;
}

/*Stack calculator */
double stackMachine(double x, TokenArr_t * expressionArr)
{
    Stack_t *head = NULL;
    double temp = 0;
    Cast_t * castUnion = NULL; // Used for unify stack. For contain double/int in void *
    /*
      If you want you can use *(void **)&x: Only for 64 bit systems. Type punning. Double cast to void * (void * will contain double value)
      instead of Cast_t union
    */

    for(int i = 0; i < expressionArr->capacity; i++, temp = 0) {
        castUnion = malloc(sizeof(Cast_t));
        switch(expressionArr->tokens[i].type) {
            case ARGUMENT:
                castUnion->d = x;
                break;
            case INT_DIGIT:
                ;
            case FLOAT_DIGIT:
                castUnion->d = atof(expressionArr->tokens[i].token);
                break;
            case FUNCTION:
                if(!strcmp(expressionArr->tokens[i].token, "sin"))
                    castUnion->d = sin(*(double *)stack_pop(&head));
                else if(!strcmp(expressionArr->tokens[i].token, "cos"))
                    castUnion->d = cos(*(double *)stack_pop(&head));
                else if(!strcmp(expressionArr->tokens[i].token, "tg"))
                    castUnion->d = tan(*(double *)stack_pop(&head));
                else if(!strcmp(expressionArr->tokens[i].token, "sqrt"))
                    castUnion->d = sqrt(*(double *)stack_pop(&head));
                else if(!strcmp(expressionArr->tokens[i].token, "abs"))
                    castUnion->d = fabs(*(double *)stack_pop(&head));
                else if(!strcmp(expressionArr->tokens[i].token, "ln"))
                    castUnion->d = log(*(double *)stack_pop(&head));
                else if(!strcmp(expressionArr->tokens[i].token, "exp"))
                    castUnion->d = exp(*(double *)stack_pop(&head));
                break;
            case OPERATOR:
                switch(expressionArr->tokens[i].token[0]) {
                    case '+':
                        castUnion->d = *(double *)stack_pop(&head) + *(double *)stack_pop(&head);
                        break;
                    case '-':
                        temp = *(double *)stack_pop(&head);
                        castUnion->d =  *(double *)stack_pop(&head) - temp;
                        break;
                    case '*':
                        castUnion->d =  *(double *)stack_pop(&head) * *(double *)stack_pop(&head);
                        break;
                    case '/':
                        temp = *(double *)stack_pop(&head);
                        castUnion->d =  *(double *)stack_pop(&head) / temp;
                        break;
                    case '%':
                        temp = *(double *)stack_pop(&head);
                        castUnion->d = fmod(*(double *)stack_pop(&head), temp);
                        break;
                    case '^':
                        temp = *(double *)stack_pop(&head);
                        castUnion->d = pow(*(double *)stack_pop(&head), temp);
                }
        }
        stack_push(&head, castUnion);
    }
    return *(double *)stack_pop(&head);
}

/*
    strtok like interface to interact with lib:
        - x: argument;
        - strWithExpression: string with math expression. Possible values:
            - string = compute and cache arr of tokens in RPN (if already arr cached, old cache will be freed);
            - CONTINUE_WITH_CACHE = continue use cached arr;
            - FREE_CACHE = frees a cached arr.
*/
double calculateFromStr(double x, char *strWithExpression)
{
#define IS_NEEDED_FREE(strWithExpression) strWithExpression[0] != -1
    static TokenArr_t *expressionArr = NULL;

    if(strWithExpression != CONTINUE_WITH_CACHE) {
        if(expressionArr) {
            for(int i = 0; i < expressionArr->capacity; i++)
                free(expressionArr->tokens[i].token);
            free(expressionArr->tokens);
            free(expressionArr);
            expressionArr = NULL;
        }
        if(!IS_NEEDED_FREE(strWithExpression)) {
            expressionArr = rpnTranslator(_strtok(strWithExpression));
            return stackMachine(x, expressionArr);
        }
    } else  if(strWithExpression == CONTINUE_WITH_CACHE && expressionArr)
        return stackMachine(x, expressionArr);

    return 0;
#undef IS_NEEDED_FREE(strWithExpression)
}