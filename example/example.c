#include <stdio.h>
#include <calc.h>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091

int main()
{
    char *testStr = "2*(cos(x)+sin(x))/sqrt(abs(x-2))";
    double x = -PI;

    printf("Expression:\t%s\n\t x = %.64g\n\tResult1 = %.64g\n", testStr, x, calculateFromStr(x, testStr));
    printf("Expression:\t%s\n\t x = %.64g\n\tResult2 = %.64g\n", testStr, x, calculateFromStr(x, CONTINUE_WITH_CACHE)); // continue computes with cached parsed string of math expressions
    calculateFromStr(x, FREE_CACHE); //frees cache
    testStr = "2*(cos(x)+sin(x))/sqrt(abs(x))";
    printf("Expression:\t%s\n\t x = %.64g\n\tResult3 = %.64g\n", testStr, x, calculateFromStr(x, testStr));
    printf("Expression:\t%s\n\t x = %.64g\n\tResult4 = %.64g\n", testStr, x, calculateFromStr(x, CONTINUE_WITH_CACHE));
    testStr = "3*(cos(x)+sin(x))/sqrt(abs(x))";
    printf("Expression:\t%s\n\t x = %.64g\n\tResult5 = %.64g\n", testStr, x, calculateFromStr(x, testStr)); // cache automatically frees without memory leak
    printf("Expression:\t%s\n\t x = %.64g\n\tResult6 = %.64g\n", testStr, x, calculateFromStr(x, CONTINUE_WITH_CACHE));
    calculateFromStr(x, FREE_CACHE);
    printf("Expression:\t%s\n\t x = %.64g\n\tResult7 = %.64g\n", testStr, x, calculateFromStr(x, CONTINUE_WITH_CACHE)); //segfault, cache freed

    return 0;
}
