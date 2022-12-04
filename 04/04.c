#include <stdio.h>

struct area {
  int start;
  int end;
};

/*
 * Checks whether the given 'inner' area is a subset of 'outer' area.
 * @return 1 if the outer area fully contains the inner area, 0 otherwise
 */
int contains(struct area *outer, struct area *inner)
{
  for (int i = inner->start; i <= inner->end; ++i)
    if (i < outer->start || i > outer->end)
      return 0;
  return 1;
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  int count = 0;
  struct area a1, a2;

  while (fscanf(file, "%d-%d,%d-%d\n", &a1.start, &a1.end, &a2.start, &a2.end) != EOF)
    if (contains(&a1, &a2) || contains(&a2, &a1))
      count++;

  printf("Count: %d\n", count);
}
