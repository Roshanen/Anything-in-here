#include <stdio.h>
int fib(int n)
{
    return (n < 2) ? n : fib(n - 2) + fib(n - 1);
}
int main()
{
    int x, n = -1;
    scanf("%d", &x);
    while (1)
    {
        n++;
        if (fib(n - 1) > x)
        {
            printf("%d is NOT FIBONACCI", x);
            break;
        }
        else if (fib(n - 1) == x)
        {
            printf("%d is FIBONACCI", x);
            break;
        }
        else
        {
            continue;
        }
    }
    return 0;
}