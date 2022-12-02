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

int main()
{
  FILE *file = fopen("input.txt", "r");
  char *line = malloc(MAX_LINE_LEN);

  int max = 0, sum = 0;

  while (read_line(file, line) == 1) {
    if (strcmp(line, "") == 0) {
      if (sum > max)
        max = sum;
      sum = 0;
    }
    else
      sum += strtol(line, NULL, 10);
  }

  printf("Max calories: %d\n", max);
  free(line);
  fclose(file);
}
