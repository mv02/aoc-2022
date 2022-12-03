#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 50

/*
 * Looks for the first duplicate character in two strings.
 * @return The duplicate character if found, otherwise '\0'
 */
char find_duplicate(char *s1, char *s2)
{
  for (int i = 0; i < (int)strlen(s1); ++i)
    for (int j = 0; j < (int)strlen(s2); ++j)
      if (s1[i] == s2[j])
        return s1[i];
  return '\0';
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  int sum = 0;
  char *line = malloc(MAX_LINE_LEN);

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
    char item = find_duplicate(left, right);

    // a-z -> 01-26
    // A-Z -> 27-52
    sum += item;
    if (item >= 97) sum -= 96;
    else if (item >= 65) sum -= 38;
  }

  printf("Sum: %d\n", sum);
  free(line);
  fclose(file);
}
