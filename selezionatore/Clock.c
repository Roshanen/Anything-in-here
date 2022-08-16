#include <stdio.h>
int main()
{
  int x, y = 30;
  scanf("%d.%2d", &x, &y);
  if (x <= 0 || x > 24 || y >= 60 || y < 0)
    printf("ERROR!\n");
  else
  {
    if (x == 24)
      printf("%02d.%02d AM\n", x - 12, y);
    else if (x > 12)
      printf("%02d.%02d PM\n", x - 12, y);
    else if (x == 12)
      printf("%02d.%02d PM\n", x, y);
    else
      printf("%02d.%02d AM\n", x, y);
  }
  return 0;
}