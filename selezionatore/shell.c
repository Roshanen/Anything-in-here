#include <stdio.h>
int main()
{
    int x, y;
    scanf("(%d,%d)", &x, &y);
    if (x >= 1 && x <= 10 && y <= 10 && y >= 1)
    {
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                if (x == j && y == i)
                    printf("@");
                else
                    printf("#");
            }
            printf("\n");
        }
    }
    else
        printf("ERROR!");
    return 0;
}