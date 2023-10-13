#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);
  int *arr = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
    scanf("%d", arr + i);

  int max = arr[0], min = arr[0];
  int amazing_performances = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
      amazing_performances++;
    } else if (arr[i] < min) {
      min = arr[i];
      amazing_performances++;
    }
  }

  printf("%d\n", amazing_performances);
}
