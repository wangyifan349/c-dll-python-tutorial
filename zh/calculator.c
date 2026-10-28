#include <stdio.h>

/* 编译 DLL 时导出函数；编译 EXE 时这个宏不会影响普通运行。 */
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

/* 成功返回 1，除数为 0 时返回 0。 */
DLL_API int divide(double a, double b, double *result)
{
    if (b == 0.0) {
        return 0;
    }

    *result = a / b;
    return 1;
}

/* 这个 main 让同一个 C 文件也可以直接编译成 EXE。 */
int main(void)
{
    double result;

    printf("2 + 3 = %.2f\n", add(2, 3));
    printf("8 - 3 = %.2f\n", subtract(8, 3));
    printf("4 * 5 = %.2f\n", multiply(4, 5));

    if (divide(10, 2, &result)) {
        printf("10 / 2 = %.2f\n", result);
    } else {
        printf("不能除以 0\n");
    }

    return 0;
}
