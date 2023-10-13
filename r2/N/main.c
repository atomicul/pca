#include <stdio.h>
#include <stdlib.h>

void solve() {
  int n, m;
  scanf("%d %d", &n, &m);
  char *lines = calloc(n, sizeof(char));
  char *columns = calloc(m, sizeof(char));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x;
      scanf("%d", &x);
      if (x)
        lines[i] = 1, columns[j] = 1;
    }
  }

  int available_lines = 0;
  for (int i = 0; i < n; i++)
    if (!lines[i])
      available_lines++;

  int available_columns = 0;
  for (int i = 0; i < m; i++)
    if (!columns[i])
      available_columns++;

  int min =
      available_columns < available_lines ? available_columns : available_lines;
  printf("%s\n", min % 2 ? "Ashish" : "Vivek");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}
