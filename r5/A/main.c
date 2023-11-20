#include <stdio.h>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int max[2] = {0, 0};
    while (n--) {
      int x;
      scanf("%d", &x);
      if (x > max[0])
        max[0] = x;
      if (max[0] > max[1]) {
        int t = max[0];
        max[0] = max[1];
        max[1] = t;
      }
    }
    printf("%d\n", max[0] + max[1]);
  }
}
