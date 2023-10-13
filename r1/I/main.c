#include <stdio.h>
#include <stdlib.h>

int main() {
  const int FIGHT_MOVES_COUNT = 4;
  int klmn[FIGHT_MOVES_COUNT];
  for (int i = 0; i < FIGHT_MOVES_COUNT; i++)
    scanf("%d", klmn + i);

  int dragons_count;
  scanf("%d", &dragons_count);
  char *damaged_dragons = calloc(dragons_count, sizeof(char));
  for (int i = 0; i < FIGHT_MOVES_COUNT; i++)
    for (int j = klmn[i] - 1; j < dragons_count; j += klmn[i])
      damaged_dragons[j] = 1;

  int ans = 0;
  for (int i = 0; i < dragons_count; i++)
    ans += (damaged_dragons[i] ? 1 : 0);

  printf("%d\n", ans);
}
