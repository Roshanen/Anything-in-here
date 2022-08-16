#include <stdio.h>
#include <string.h>
int main()
{
    char word1;
    char word2[100];
    scanf("%c\n", &word1);
    scanf("%[^\n]s", word2);
    for (int i = 0; i < strlen(word2); i++)
    {
        if (word1 == word2[i])
        {
            break;
        }
        printf("%c", word2[i]);
    }
    return 0;
}