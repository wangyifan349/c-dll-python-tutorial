#include <stdio.h>

/* Export functions when building a DLL; harmless for a normal EXE build. */
#ifdef _WIN32
#define DLL_API __declspec(dllexport)
#else
#define DLL_API
#endif

DLL_API double add(double a, double b)
{
    return a + b;
}

DLL_API double subtract(double a, double b)
{
    return a - b;
}

DLL_API double multiply(double a, double b)
{
    return a * b;
}

/* Return 1 on success and 0 when the divisor is zero. */
DLL_API int divide(double a, double b, double *result)
{
    if (b == 0.0) {
        return 0;
    }

    *result = a / b;
    return 1;
}

/* This main function lets the same C file build directly as an EXE. */
int main(void)
{
    double result;

    printf("2 + 3 = %.2f\n", add(2, 3));
    printf("8 - 3 = %.2f\n", subtract(8, 3));
    printf("4 * 5 = %.2f\n", multiply(4, 5));

    if (divide(10, 2, &result)) {
        printf("10 / 2 = %.2f\n", result);
    } else {
        printf("Cannot divide by zero\n");
    }

    return 0;
}
