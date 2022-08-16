#include <stdio.h>
int main()
{
    int d1, d2, m1, m2;
    int day1, day2;
    int kyu[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int diff;
    scanf("%d %d", &d1, &m1);
    scanf("%d %d", &d2, &m2);
    if(d1<1||d2<1||m1<1||m2<1||m1>12||m2>12)
        printf("Invalid input");
    else if (d1 > kyu[m1]-kyu[m1-1])
        printf("Invalid input");
    else
    {
    day1 = kyu[m1 - 1] + d1;
    day2 = kyu[m2 - 1] + d2;
    diff = (day2 > day1) ? (day2 - day1) : (day1 - day2);
    printf("%d", diff);
    }
    return 0;
}