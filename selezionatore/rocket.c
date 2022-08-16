#include <stdio.h>
int main()
{
    int num, last, lod = 0;
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &num);
        lod += (num < last) ? 1 : 0;
        last = num;
    }
    printf("%d", lod);
    return 0;
}