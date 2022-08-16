#include <stdio.h>
int main()
{
    int num;
    int a, b, c;
    scanf("%d",&num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d %d", &a, &b);
        c = (a > b) ? (a - b) : (b - a);
        if (c % 10 == 0)
        {
            printf("%d", c/10);
        }
        else
        {
            printf("%d", c/10+1);
        }
        printf("\n");
    }
    return 0;
}