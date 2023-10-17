#include <stdio.h>

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}

int main() {
  char str[128];
  fgets(str, 128, stdin);
  for (char *ch = str; *ch; ch++) {
    if (*ch < 'a' || *ch > 'z') {
      *ch = 0;
      break;
    }
  }

  char ptr = 'a';
  int acc = 0;
  for (char *ch = str; *ch; ptr = *(ch++)) {
    if (*ch >= ptr) {
      acc += min(*ch - ptr, ptr - *ch + 26);
    } else {
      acc += min(ptr - *ch, *ch - ptr + 26);
    }
  }
  printf("%d\n", acc);
}
