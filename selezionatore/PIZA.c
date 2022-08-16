#include <stdio.h>
int main()
{
    int h;
    scanf("%d", &h);
    if (h < 2)
        printf("ERROR!");
    else
    {
        for (int i = 1; i < h + 1; i++)
        {
            for (int j = 0; j < i; j++)
            {
                for (int k = 0; k < i - 1; k++)
                {
                    printf(" ");
                }
                for (int l = 0; l < h; l++)
                {
                    {
                        printf("#");
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}