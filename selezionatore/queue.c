#include <stdio.h>

int main()
{
  int index;
  scanf("%d", &index);
  int num[index];
  for (int i = 0; i < index; i++)
  {
    scanf("%d", &num[i]);
    if (num[i] <= 0)
    {
      printf("Invalid Input");
      return 0;
    }
  }
  for (int i = 0; i < index; i++)
  {
    if (num[i] % 2 == 0)
      printf("%d ", num[i]);
  }
  for (int i = 0; i < index; i++)
    if (num[i]%2 == 1)
      printf("%d ", num[i]);
  return 0;
}