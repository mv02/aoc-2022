#include <stdio.h>

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

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

/*
 * Checks whether two areas have overlapping sections.
 * @return 1 if the areas overlap, 0 otherwise
 */
int overlap(struct area *a1, struct area *a2)
{
  return (MAX(a1->start, a2->start)) <= (MIN(a1->end, a2->end));
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  int count1 = 0, count2 = 0;
  struct area a1, a2;

  while (fscanf(file, "%d-%d,%d-%d\n", &a1.start, &a1.end, &a2.start, &a2.end) != EOF) {
    if (contains(&a1, &a2) || contains(&a2, &a1))
      count1++;
    if (overlap(&a1, &a2))
      count2++;
  }

  printf("Subsets: %d\n", count1);
  printf("Overlapping: %d\n", count2);
}
