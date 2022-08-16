#include <stdio.h>
int main()
{
    int a=0, b=0, n;
    scanf("%d", &n);
    int x[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (x[i] > 0)
        a += 1;
        else if (x[i] < 0)
        b += 1;
    }
    printf("%d\n%d",a,b);
    return 0;
}