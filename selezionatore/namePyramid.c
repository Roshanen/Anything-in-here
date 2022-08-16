#include <stdio.h>
#include <string.h>
int main() {
  int mid,left,right;
 char word[100];
  scanf("%s",&word);
  mid=strlen(word);
  for(int i=0;i<mid;i++)
  {
    for(int k=mid;k>0;k--)
    {
      if(i+1>k)
      printf("%c ",word[k]);
      else if(k==mid)
      continue;
      else
      printf("  ");
    }
    for(int j=0;j<(2*mid);j++)
    {
      if(i+1>j)
    printf("%c ",word[j]);
    }
    printf("\n");
  }
 return 0;
}