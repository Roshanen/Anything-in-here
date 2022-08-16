#include<stdio.h>
int main() {
 int a,b,h;
  scanf("%d %d %d",&a,&b,&h);
  h -= a;
  int ans = 1;
  if(h%(a-b)>0){
    ans += 1;
  }
  ans += h/(a-b);
  printf("%d",ans);
 return 0;
}