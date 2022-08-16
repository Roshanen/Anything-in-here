#include <stdio.h>
#include <string.h>
int main()
{
    char num[5000];
    unsigned long long int sum = 0, tod = 0;
    scanf("%[^\n]s", num);
    for (int i = 0; i < strlen(num) + 1; i++)
    { // 48-57
        if (47 < num[i] && num[i] < 58)
        {
            tod = tod * 10 + (num[i] - '0');
        }
        else
        {
            sum += tod;
            tod = 0;
        }
    }
    printf("%llu", sum);
    return 0;
}