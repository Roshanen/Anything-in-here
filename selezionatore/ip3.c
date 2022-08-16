#include <stdio.h>
int main()
{
    int num, que;
    int dec[8] = {255, 128, 192, 224, 240, 248, 252, 254};
    scanf("%d", &num);
    que = num % 8;
    if (num == 0)
        printf("0.0.0.0");
    else if (num >= 1 && num <= 8)
        printf("%d.0.0.0", dec[que]);
    else if (num >= 9 && num <= 16)
        printf("255.%d.0.0", dec[que]);
    else if (num >= 17 && num <= 24)
        printf("255.255.%d.0", dec[que]);
    else if (num >= 24 && num <= 32)
        printf("255.255.255.%d", dec[que]);
    else
        printf("error");
    return 0;
}