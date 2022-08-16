#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char word[100];
    scanf("%[^\n]", word);
    int L = strlen(word);
    for (int i = 0; i < L; i++)
    {
        char A = tolower(word[i]);
        char a = toupper(word[i]);
        switch (word[i])
        {
        case 'A' ... 'Z':
        {
            printf("%c", A);
            break;
        }
        case 'a' ... 'z':
        {
            printf("%c", a);
            break;
        }
        default:
        {
            printf("%c", word[i]);
        }
        }
    }
    return 0;
}