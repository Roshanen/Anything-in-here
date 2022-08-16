#include <stdio.h>

int main()
{
    int sum = 0; 
    int num; 
    int fact = 0;
    scanf("%d", &num);
    fact = (num < 0) ? 1 : 0;
    num = (num < 0) ? (-num) : (num);

    /*if (0 < num < 9)
    {
        printf((fact == 0) ? ("%d") : ("-%d"), num);
    }
    else*/
    if(num>9)
    {
        while (num > 10)
        {
            while (num > 0)
            {
                int mod;
                mod = num % 10;
                sum += mod;
                num /= 10;
            }
            if (sum > 9)
            {
                num = sum;
                sum = 0;
            }

        }
        printf((fact == 0) ? ("%d") : ("-%d"), sum);
    }
    else
    {
        printf((fact == 0) ? ("%d") : ("-%d"), num);
    }
    return 0;
}