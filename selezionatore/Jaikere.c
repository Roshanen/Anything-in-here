#include<stdio.h>
#include<string.h>
int main() {
 char word[1000];
  scanf("%s", &word);
  for(int i=0;i<strlen(word);i++)
  {
    printf("%c ", word[i]);
  }
 return 0;
}