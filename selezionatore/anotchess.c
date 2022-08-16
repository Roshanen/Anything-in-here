#include<stdio.h>
int main() {
 int x,y,i;
  scanf("%d %d",&x,&y);
  i=0;
  if(x<3||y<3)
  {
    printf("ERROR!");
  }
  else
  {
    for(i=0;i<x;i++)
    {
    if(i%2==0)
    {
      for(int j=0;j<y;j++)
      {
        printf((j%2==0)?"O":"X");
      }
    }  

    else
    {
      for(int j=0;j<y;j++)
      {
        printf((j%2==0)?"X":"O");
      }
    }
    printf("\n");
    }
  }
 return 0;
}