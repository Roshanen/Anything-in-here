#include<stdio.h>
#include<string.h>
int main() {
  int dex, len;
 char word[10000];
  scanf("%[^\n]s",&word);
  len = strlen(word);
  dex = 'M' - word[len-11];
  for(int i=0;i<len;i++)
    {
      if(word[i]>64&&word[i]<91)
      {
      word[i] = ((word[i] - 'A' + dex)%26 + 65) ;
      if(word[i]<65)
       word[i]=91-(65-(word[i]));
      printf("%c",word[i]);
      }
      else if(word[i]>96&&word[i]<123)
      {
      word[i] = ((word[i] - 'a' + dex)%26 + 97) ;
      if(word[i]<97)
       word[i]=123-(97-(word[i]));
      printf("%c",word[i]);
      }
      else
        printf("%c",word[i]);
    }
 return 0;
}