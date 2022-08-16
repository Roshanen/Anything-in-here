#include <stdio.h>
#include <string.h>
int main()
{
    int dex;
    char word[1000];
    scanf("%d %s", &dex, &word);

    if (dex <= 0)
        printf("ERROR");
    else
    {
        printf("ROT%d of %s is ", dex, word);
        for (int i = 0; i < strlen(word); i++)
        {
            if (64 < word[i] && word[i] < 91)
            { // 65-90
                word[i] = (word[i] + dex - 'A') % 26 + 65;
                printf("%c", word[i]);
            }
            else if (96 < word[i] && word[i] < 123)
            { // 97-122
                word[i] = (word[i] + dex - 'a') % 26 + 97;
                printf("%c", word[i]);
            }
            else
                printf("%c", word[i]);
        }
    }
    return 0;
}