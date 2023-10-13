#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int map_size = 1 << 6;
const int vec_initial_capacity = 4;

typedef struct map_pair {
  const char *str;
  int cnt;
} map_pair;

typedef struct vector {
  map_pair *a;
  int size, capacity;
} vector;

int hash_str(const char *str) {
  long long acc = 1;
  long long p = 31;
  for (const char *i = str; *i; i++) {
    acc += p * (*i - 'a' + 1);
    p = p * p % map_size;
    acc %= map_size;
  }
  return acc;
}

map_pair *get_map(const vector *map, const char *str) {
  int pos_in_map = hash_str(str);
  vector vec = map[pos_in_map];

  int pos_in_vec = 0;
  for (; pos_in_vec < vec.size; pos_in_vec++)
    if (!strcmp(vec.a[pos_in_vec].str, str))
      break;

  if (pos_in_vec == vec.size)
    return NULL;

  return &vec.a[pos_in_vec];
}

void insert_vec(vector *v, const map_pair *x) {
  if (v->size + 1 > v->capacity)
    v->a = realloc(v->a, sizeof(map_pair) * 2 * v->capacity), v->capacity *= 2;
  v->a[v->size] = *x;
  v->size++;
}

void count_map(vector *map, const char *str) {
  int pos = hash_str(str);
  map_pair *p = get_map(map, str);
  if (p) {
    p->cnt++;
    return;
  }

  char *str_cpy = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(str_cpy, str);
  map_pair x = {str_cpy, 1};
  insert_vec(map + pos, &x);
}

void free_map(vector *map) {
  for (int i = 0; i < map_size; i++) {
    vector *vec = map + i;
    for (int j = 0; j < vec->size; j++)
      free(vec->a[j].str);
    free(vec->a);
  }
  free(map);
}

int main() {
  vector *map = calloc(sizeof(vector), map_size);
  for (int i = 0; i < map_size; i++)
    map[i].a = malloc(sizeof(map_pair) * vec_initial_capacity),
    map[i].capacity = vec_initial_capacity;

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    char str[256];
    scanf("%s", str);
    map_pair *x = get_map(map, str);
    if (!x)
      puts("OK");
    else
      printf("%s%d\n", str, x->cnt);
    count_map(map, str);
  }
  free_map(map);
}
