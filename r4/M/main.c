#include <stdio.h>
#include <string.h>

char allCharsEq(const char *s) {
  for (; s[1]; s++)
    if (s[0] != s[1])
      return 0;
  return 2;
}

char isPal(const char *s) {
  int n = strlen(s);
  for (int i = 0, j = n - 1; i < j; i++, j--)
    if (s[i] != s[j])
      return 0;
  return 1;
}

int main() {
  int t;
  scanf("%d", &t);
  getc(stdin);
  while (t--) {
    char str[64];
    fgets(str, 64, stdin);
    for (char *p = str; *p; p++)
      if (*p == '\n')
        *p = '\0';

    int n = strlen(str);
    if (n == 1) {
      puts("-1");
    } else if (n == 2) {
      printf("%d\n", str[0] == str[1] ? -1 : 2);
    } else if (allCharsEq(str)) {
      printf("%d\n", -1);
    } else if (isPal(str)) {
      printf("%d\n", n - 1);
    } else {
      printf("%d\n", n);
    }
  }
}
