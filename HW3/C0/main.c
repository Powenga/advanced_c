#include <stdio.h>
#include <string.h>

#define MAX 100000

int main()
{
  char s[MAX];
  scanf("%s", s);

  int len = strlen(s);
  int used[1000] = {0}; // числа от 100 до 999
  int count = 0;

  for (int i = 0; i < len - 2; i++)
  {
    if (s[i] == '0')
      continue; // не трёхзначное

    for (int j = i + 1; j < len - 1; j++)
    {
      for (int k = j + 1; k < len; k++)
      {

        int num = (s[i] - '0') * 100 +
                  (s[j] - '0') * 10 +
                  (s[k] - '0');

        if (!used[num])
        {
          used[num] = 1;
          count++;
        }
      }
    }
  }

  printf("%d\n", count);
  return 0;
}