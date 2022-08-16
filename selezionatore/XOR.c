#include <stdio.h>
int main()
{
    char word[2];
    scanf("%s", &word);

    printf("%d",word[0]^word[1]);
    return 0;
}