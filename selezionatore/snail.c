#include <stdio.h>
int main()
{
  int A, B, H;
  int X, Y, Z;
  scanf("%d %d %d", &A, &B, &H);
  X=H/(A-B)-10;
  Y=X*(A-B);
  Z=H-Y;
  while(Z>0)
  {
    Z=Z-A;

    if(Z>0)
    {
    Z=Z+B;
    X+=1;
    }
    else
    {
    X+=1;
    break;
    }
  }
printf("%d",X);
  return 0;
}