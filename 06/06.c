#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 5000

int get_marker_position(char *data, int marker_len)
{
  int len = strlen(data);
  int i, j, k;

  for (i = 0; i <= len - marker_len; ++i) {
    int duplicate = 0;

    for (j = i; j < i + marker_len - 1; ++j) {
      for (k = j + 1; k < i + marker_len; ++k)
        if (data[j] == data[k]) {
          duplicate = 1;
          break;
        }

      if (duplicate) break;
    }

    if (!duplicate) break;
  }

  return k;
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  char *input = malloc(MAX_INPUT_LEN);
  fscanf(file, "%s\n", input);

  printf("Packet start marker: %d\n", get_marker_position(input, 4));
  printf("Message start marker: %d\n", get_marker_position(input, 14));

  free(input);
  fclose(file);
}
