#include<stdio.h>
int main() {
 int x;
  scanf("%d",&x);
  if(x<1)
  printf("ERROR!");
  else
  {
  for(int i=0;i<x;i++)
    {
    if(i==0||i==x-1)
      {
      for(int j=0;j<x;j++)
        printf("#");
      }
    else
      {
      printf("#");
      for(int j=0;j<x-2;j++)
      {
      printf(" ");
      }
      printf("#");
      }
      printf("\n");
    }
  }
 return 0;
}