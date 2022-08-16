#include <stdio.h>
int main()
{
    int n, index = 0;
    scanf("%d", &n);
    for (int i = 1; i < 100000; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            index++;
            if (index == n)
            {
                printf("%d", j);
                break;
            }
        }
        if (index == n)
            break;
    }
    return 0;
}