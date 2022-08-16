#include <stdio.h>
#include <string.h>
int main()
{
    int x = 0, y = 0;
    for (int i = 0; i < 10; i++)
    {
        int move = 0;
        char com[20] = "\0";
        scanf("%s %d", &com, &move);
        if (strlen(com) == 7)
            x += move;
        else if (strlen(com) == 2)
            y += move;
        else
            y -= move;
    }
    printf("%d", (x * y > 0) ? x * y : -(x * y));
    return 0;
}