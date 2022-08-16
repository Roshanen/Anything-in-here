#include<stdio.h>
int main() {
 int num,i=0;
  int quo=2;
  scanf("%d",&num);
  if (num<2)
  {
    printf("ERROR!");
    return 0;
  }
  while(num>1)
    {
      if(num%quo==0 && i==0)
      {
        i++;
        printf("%d ",quo);
        num/=quo;
      }
    if(num%quo==0)
      {
        printf("x %d ",quo);
        num/=quo;        
      }
      else
        quo++;
    }

 return 0;
}