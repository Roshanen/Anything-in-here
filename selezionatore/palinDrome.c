#include <stdio.h>
#include <string.h>
int main()
{
    char num[100];
    scanf("%s", &num);
    int left = 0, right = strlen(num) - 1;
    while (num[left] == '0')
    {
        if (left == right && num[right] == '0')
        {
            printf("0 is PALINDROME");
            return 0;
        }
        else
            left += 1;
    }
    for (int i = left; i <= right; i++)
        printf("%c", num[i]);
    while (left < right)
    {
        if (num[left] == num[right])
        {
            left++;
            right--;
            continue;
        }
        else
        {
            printf(" is NOT PALINDROME");
            return 0;
        }
    }
    printf(" is PALINDROME");
    return 0;
}