# How to. Simple guide and docs.
## Functions
### _strtok()
function 	**_strtok()** - parser of math expressions. Takes a string with math expressions, parses  math operators, forms and return an array of tokens with this operators
#### Arguments:
>- char expressionStr[] - null-terminated string with any count of separators. Contain math expression
#### Return value:
>- TokenArr_t tokenArr[] 
### rpnTranslator()
function **rpnTranslator()** - translator from infix notation to postfix. Takes an array of tokens with math operators and returns  this array in reverse Poland notation 
#### Arguments:
>- TokenArr_t inputTokenArr[]
#### Return value
>- TokenArr_t outputTokenArr[] - in RPN
### stackMachine()
function **stackMachine()** - stack calculator. Takes an array of tokens with math operators in RPN and value of argument x and  returns  calculated value for math expreesion in array of tokens.
#### Arguments:
>- TokenArr_t inputTokenArr[] - in RPN. 
>- double x - argument
#### Return value
>- double result - result of calculation
### calculateFromStr()
function **calculateFromStr()** - an easy to use wrapper. **strtok()**-like interface for interaction with lib. Takes a string with math expressions and value of argument x and returns calculated value for expression in string. Also has internal cache. 
#### Arguments
>- char expressionStr[] - null-terminated string with any count of separators. Contain math expression.
> ##### Possible values:
>>- char str[] - compute and cache arr of tokens in RPN (if already arr cached, old cache will be freed)
>>- CONTINUE_WITH_CACHE - continue compute by using cached arr
>>- FREE_CACHE = frees a cached arr
>- double x - argument
#### Return value
>- double result - result of calculations
## Types
### TokenArr_t
**TokenArr_t** - type that just implement an array of variable with type **Token_t**
#### Fields
>- int capacity - capacity of array
>- Token_t tokens[] - array of tokens
### Token_t
**Token_t** - type that contains single math expression/operator
#### Fields
>- char token[] - null-terminated string. Introduce how math operator looks
>- int type: 4 - bit field that contain id of type of math operator
> ##### Possible values:
>>- ARGUMENT - argument x
>>- INT_DIGIT - integer number
>>- FLOAT_DIGIT - float number
>>- FUNCTION - math function like sin etc.
>>- OPERATOR - math operator like + - * / etc.
>>- OPENING_BRACKET - (
>>- CLOSING_BRACKET - )
>- int prio: 3 - bit field that contain priority of math operator/function
> ##### Possible values:
>>- NO_PRIO - no priority. For numbers and brackets etc.
>>- LOWEST_PRIO - the lowest priority. For + - etc.
>>- AVARAGE_PRIO - avarage priority. For * /  etc.
>>- HIGH_PRIO - high priority. For ^ etc.
>>- HIGHEST_PRIO - the highes priority. For functions.
### Cast_t
**Cast_t** - Union. Type that needs to push inside the stack values of double/int/char etc. types
#### Fields
>- double d
>- long long int li
>- float f
>- int i
>- short s
>- char c
