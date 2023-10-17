#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);
  n *= 2;
  int *socks = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    scanf("%d", socks + i);
  int m = 0;
  int *stk = malloc(n * sizeof(int));

  int ans = 0;
  while (n) {
    while (n && m && socks[n - 1] == stk[m - 1])
      n--, m--, ans++;
    if (n)
      stk[m++] = socks[--n], ans++;
  }
  if (m)
    puts("impossible");
  else
    printf("%d\n", ans);
}
