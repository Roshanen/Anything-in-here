#include <stdio.h>
int lad(int n)
{
    return (n < 4) ? n : lad(n - 2) + lad(n - 1);
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", lad(n));
    return 0;
}