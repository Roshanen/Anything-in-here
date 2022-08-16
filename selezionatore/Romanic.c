#include<stdio.h>
#include<string.h>
int main() {
 char word[4000];
  int sum=0;
  scanf("%s",&word);
  for(int i=0;i<strlen(word);i++)
    {
      if(word[i]=='I')
        sum+=1;
      else if(word[i]=='V')
        sum+=(word[i-1]=='I'?3:5);
      else if(word[i]=='X')
        sum+=(word[i-1]=='I'?8:10);
      else if(word[i]=='L')
        sum+=(word[i-1]=='X'?30:50);
      else if(word[i]=='C')
        sum+=(word[i-1]=='X'?80:100);
      else if(word[i]=='D')
        sum+=(word[i-1]=='C'?300:500);
      else if(word[i]=='M')
        sum+=(word[i-1]=='C'?800:1000);
    }
  printf("%d",sum);
return 0;
}