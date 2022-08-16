#include <stdio.h>
#include <string.h>
char a3toc(const char *ptr)
{
    return (ptr[0] - '0') * 100 + (ptr[1] - '0') * 10 + (ptr[2] - '0');
}
int main()
{
    char box[10000];
    char word[3];
    scanf("%s", &box);
    for (int i = 0; i < strlen(box) ; i += 3)
    {
        for (int j = 0; j < 3; j++)
        {
            word[j] = box[i+j];
        }
        printf("%c", a3toc(word));
    }
    return 0;
}