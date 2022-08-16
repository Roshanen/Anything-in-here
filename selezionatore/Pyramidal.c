#include <stdio.h>

int main()
{
    int a,b;
    scanf("%d %d",&a, &b);
    for(int i=0;i<a+1;i++)
    {
        for(int k=a-i;k>0;k--)
        {
            printf(" ");
        }
        for(int j=0;j<i+1;j++)
        {
        printf("* ");
        }
        printf("\n");
    }
return 0;
}