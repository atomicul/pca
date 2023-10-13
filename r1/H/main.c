#include <stdio.h>
#include <stdlib.h>

int main() {
  const int SHOES_COUNT = 4;
  int shoes_color[SHOES_COUNT];
  for (int i = 0; i < SHOES_COUNT; i++)
    scanf("%d", &shoes_color[i]);

  for (int i = 0; i < SHOES_COUNT; i++) {
    for (int j = i + 1; j < SHOES_COUNT; j++) {
      if (shoes_color[i] > shoes_color[j]) {
        int tmp = shoes_color[i];
        shoes_color[i] = shoes_color[j];
        shoes_color[j] = tmp;
      }
    }
  }

  int duplicate_shoes = 0;
  for (int i = 1; i < SHOES_COUNT; i++)
    duplicate_shoes += shoes_color[i] == shoes_color[i - 1];

  printf("%d\n", duplicate_shoes);
}
