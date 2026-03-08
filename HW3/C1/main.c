#include <stdio.h>
#include <string.h>

#define MAX_LEN 10001 // +1 для нуль-терминатора

int main()
{
  char s1[MAX_LEN], s2[MAX_LEN];

  // Считываем строки
  fgets(s1, MAX_LEN, stdin);
  s1[strcspn(s1, "\n")] = '\0'; // убираем перевод строки

  fgets(s2, MAX_LEN, stdin);
  s2[strcspn(s2, "\n")] = '\0';

  int len1 = strlen(s1);
  int len2 = strlen(s2);

  // 1. Наибольший префикс s1, являющийся суффиксом s2
  int pref_count_s1 = 0;
  int min_len = len1 < len2 ? len1 : len2;

  for (int len = 1; len <= min_len; len++)
  {
    // Проверяем, является ли префикс s1 длины len суффиксом s2
    if (strncmp(s1, s2 + len2 - len, len) == 0)
    {
      pref_count_s1 = len;
    }
  }

  // 2. Наибольший суффикс s1, являющийся префиксом s2
  int pref_count_s2 = 0;

  for (int len = 1; len <= min_len; len++)
  {
    // Проверяем, является ли суффикс s1 длины len префиксом s2
    if (strncmp(s1 + len1 - len, s2, len) == 0)
    {
      pref_count_s2 = len;
    }
  }

  // Выводим результат
  printf("%d %d\n", pref_count_s1, pref_count_s2);

  return 0;
}