#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 8

typedef struct StringList {
  int size, capacity;
  char **strings;
} StringList;

int strcmpadapter(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

char *slget(const StringList *x, int pos) { return x->strings[pos]; }
int slsize(const StringList *x) { return x->size; }
void slinsert(StringList *x, const char *s) {
  if (x->size >= x->capacity) {
    x->strings = realloc(x->strings, sizeof(char *) * x->capacity * 2);
    x->capacity *= 2;
  }
  x->strings[x->size] = calloc(strlen(s) + 1, sizeof(char));
  strcpy(x->strings[x->size], s);
  x->size++;
}
void slfree(StringList *x) {
  for (int i = 0; i < slsize(x); i++) {
    free(x->strings[i]);
    x->strings[i] = NULL;
  }
  free(x->strings);
  x->strings = NULL;
  free(x);
}
void slsort(StringList *x) {
  qsort(x->strings, x->size, sizeof(char *), strcmpadapter);
}
char slbsearch(StringList *x, const char *s) {
  int l = 0, h = slsize(x);
  while (l < h) {
    int mid = (l + h) / 2;
    int cmp = strcmp(slget(x, mid), s);
    if (cmp == 0)
      return 1;

    if (cmp < 0)
      l = mid + 1;
    else
      h = mid;
  }
  return 0;
}
StringList *sl() {
  StringList *x = calloc(1, sizeof(StringList));
  x->size = 0;
  x->capacity = 4;
  x->strings = calloc(x->capacity, sizeof(char *));
  return x;
}

void solve() {
  StringList *buckets[MAX_STR_LEN];
  for (int i = 0; i < MAX_STR_LEN; i++)
    buckets[i] = sl();

  int n;
  StringList *original_order = sl();
  scanf("%d", &n);
  getc(stdin);
  for (int i = 0; i < n; i++) {
    char s[MAX_STR_LEN + 2];
    fgets(s, MAX_STR_LEN + 2, stdin);
    for (char *p = s; *p; p++)
      if (*p == '\n')
        *p = '\0';
    slinsert(buckets[strlen(s) - 1], s);
    slinsert(original_order, s);
  }
  for (int i = 0; i < MAX_STR_LEN; i++) {
    slsort(buckets[i]);
  }

  for (int i = 0; i < slsize(original_order); i++) {
    const char *str = slget(original_order, i);
    int len = strlen(str);
    int j = 1;
    for (; j < len; j++) {
      char a[MAX_STR_LEN + 1];
      for (int i = 0; i < MAX_STR_LEN + 1; i++)
        a[i] = '\0';
      strncpy(a, str, j);
      if (slbsearch(buckets[j - 1], a) &&
          slbsearch(buckets[len - j - 1], str + j))
        break;
    }
    printf("%i", j != len);
  }
  printf("\n");
  for (int i = 0; i < MAX_STR_LEN; i++) {
    slfree(buckets[i]);
  }
  slfree(original_order);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}
