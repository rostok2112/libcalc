#include <types.h>

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
#undef IS_NEEDED_FREE
}