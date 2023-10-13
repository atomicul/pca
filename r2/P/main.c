#include <stdio.h>
#include <stdlib.h>

const int MAX_NEIGHBORS = 4;

void print_solution(int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x = MAX_NEIGHBORS;
      x -= i == 0 || i == n - 1;
      x -= j == 0 || j == m - 1;
      printf("%d ", x);
    }
    puts("");
  }
}

void solve() {
  int n, m;
  scanf("%d %d", &n, &m);

  char impossible = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x = MAX_NEIGHBORS;
      x -= i == 0 || i == n - 1;
      x -= j == 0 || j == m - 1;
      int el;
      scanf("%d", &el);
      if (el > x)
        impossible = 1;
    }
  }

  if (impossible)
    puts("NO");
  else {
    puts("YES");
    print_solution(n, m);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}
