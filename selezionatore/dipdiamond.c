#include <stdio.h>
int main()
{
    int n, mid;
    int length, bot;
    scanf("%d", &n);
    if (n < 3)
        printf("ERROR!");
    mid = (n % 2 == 0) ? (n / 2) : (n / 2 + 1);
    bot = n - mid;
    length = (n % 2 == 0) ? (n - 1) : (n);
    for (int i = 0; i < mid; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (j == mid - 1 + i % mid || j == mid - 1 - i % mid)
            {
                printf("*");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    for (int i = bot - 1; i >= 0; i--)
    {
        for (int j = 0; j < length; j++)
        {
            if (j == mid - 1 - i % mid || j == mid - 1 + i % mid)
            {
                printf("*");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}
