#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 50

/*
 * Looks for the first n duplicate characters in two strings.
 * @param output The array to save found duplicates into
 * @param n How many duplicates to look for
 * @return How many duplicates have been found
 */
int find_duplicates(char *s1, char *s2, char output[], char n)
{
  int found = 0;

  for (int i = 0; i < (int)strlen(s1); ++i) {
    for (int j = 0; j < (int)strlen(s2); ++j) {
      if (s1[i] == s2[j])
        output[found++] = s1[i];
      if (found == n)
        return found;
    }
  }

  return found;
}

/*
 * Calculates the priority of given item.
 * Lowercase items (a-z) have priorities 01-26,
 * uppercase items (A-Z) have priorities 27-52.
 */
int get_priority(char item)
{
  if (item >= 97)
    return item - 96;
  if (item > 0)
    return item - 38;
  return 0;
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  int sum1 = 0, sum2 = 0, count = 0;
  char *line = malloc(MAX_LINE_LEN);
  char *group[3];
  for (int i = 0; i < 3; ++i)
    group[i] = malloc(MAX_LINE_LEN);

  while (fscanf(file, "%s\n", line) != EOF) {
    // Split the list in half
    int half = strlen(line) / 2;
    char left[MAX_LINE_LEN / 2], right[MAX_LINE_LEN / 2];
    int i;

    for (i = 0; i < half; ++i) {
      left[i] = line[i];
      right[i] = line[half + i];
    }

    // Append the null character
    left[i] = '\0';
    right[i] = '\0';

    // Find the duplicate item and add its priority
    char duplicates[1];
    find_duplicates(left, right, duplicates, 1);
    sum1 += get_priority(duplicates[0]);

    // Add current backpack to the group of 3 Elves
    strcpy(group[count % 3], line);

    // On every 3rd Elf, find the group's badge
    if (++count % 3 == 0) {
      char d1[MAX_LINE_LEN], d2[MAX_LINE_LEN], badge;
      int d1_count = find_duplicates(group[0], group[1], d1, MAX_LINE_LEN);
      int d2_count = find_duplicates(group[1], group[2], d2, MAX_LINE_LEN);

      int found = 0;

      for (int j = 0; j < d1_count && !found; ++j)
        for (int k = 0; k < d2_count && !found; ++k)
          if (d1[j] == d2[k]) {
            badge = d1[j];
            found = 1;
          }

      sum2 += get_priority(badge);
    }
  }

  printf("Sum of duplicate items: %d\n", sum1);
  printf("Sum of badges: %d\n", sum2);
  free(line);
  for (int i = 0; i < 3; ++i)
    free(group[i]);
  fclose(file);
}
