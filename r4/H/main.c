#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);

  int *a = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);

  int ans = 0;
  for (int i = 0; i + 1 < n;) {
    int l = i, r = i + 1;
    while (l >= 0 && r < n && a[l] != a[r] && a[l] == a[i])
      l--, r++;
    if (r - l - 1 > ans)
      ans = r - l - 1;
    i = r;
  }
  printf("%d\n", ans);
}
