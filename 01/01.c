#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 10

/**
 * Reads a line from given file.
 * @return 1 on success, 0 on EOF
 */
int read_line(FILE *file, char *output)
{
  if (fgets(output, MAX_LINE_LEN, file) == NULL)
    return 0;

  // Remove the trailing newline character
  output[strlen(output) - 1] = '\0';
  return 1;
}

/**
 * Inserts given element into the array of top elements if necessary.
 * @param element The element to compare
 * @param top The current array of top elements
 * @param n Size of the array
 */
void update_top(int element, int top[], int n)
{
  int min_index = n - 1, min = top[min_index];

  for (int i = 0; i < n; ++i) {
    if (top[i] < min) {
      min_index = i;
      min = top[i];
    }
  }

  if (element > min)
    top[min_index] = element;
}

int main()
{
  FILE *file = fopen("input.txt", "r");
  char *line = malloc(MAX_LINE_LEN);

  int top[] = {0, 0, 0}, sum = 0;

  while (read_line(file, line) == 1) {
    if (strcmp(line, "") == 0) {
      update_top(sum, top, 3);

      sum = 0;
    }
    else
      sum += strtol(line, NULL, 10);
  }

  printf("Max calories: %d\n", top[2]);
  printf("Sum of top 3: %d\n", top[0] + top[1] + top[2]);
  free(line);
  fclose(file);
}
