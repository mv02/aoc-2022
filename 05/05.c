#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACKS 10
#define MAX_CRATES 30

struct stack {
  int capacity;
  int size;
  char *crates;
};

void stack_init(struct stack *s, int capacity)
{
  s->capacity = capacity;
  s->size = 0;
  s->crates = malloc(capacity);
}

void stack_clear(struct stack *s)
{
  s->capacity = 0;
  s->size = 0;
  free(s->crates);
}

char stack_pop(struct stack *s)
{
  return s->crates[--s->size];
}

char stack_remove(struct stack *s, int index)
{
  char c = s->crates[index];
  for (int i = index; i < s->size - 1; ++i)
    s->crates[i] = s->crates[i + 1];
  s->size--;
  return c;
}

int stack_append(struct stack *s, char crate)
{
  s->crates[s->size++] = crate;
  return s->size;
}

/*
 * Reads the highest number from the line with stack numbers.
 * @return The number of stacks
 */
int read_stack_count(FILE *file)
{
  char *line = malloc(4 * MAX_STACKS - 1);
  // Scan the line with numbers and spaces
  fscanf(file, "%*[^0-9] %[0-9 ]", line);
  // Parse the last digit
  int count = strtol(&line[strlen(line) - 2], NULL, 10);

  free(line);
  rewind(file);
  return count;
}

/*
 * Reads the rows of crates from top to bottom.
 * @return The number of rows scanned
 */
int read_rows(FILE *file, char **rows, int stack_count)
{
  int end = 0, count = 0;

  // Repeat until the stack number line is reached
  while (!end) {
    rows[count] = malloc(stack_count);
    char c;

    // Read all characters before '\n'
    for (int i = -1; (c = fgetc(file)) != '\n'; ++i) {
      if (isdigit(c)) {
        free(rows[count]);
        end = 1;
        break;
      }

      // Every 4th character is a crate
      if (i % 4 == 0)
        rows[count][i / 4] = c;
    }

    if (end) break;
    count++;
  }

  return count;
}

/*
 * Prints all stacks next to each other.
 */
void print_supplies(struct stack *supplies, int stack_count)
{
  int max_height = 0;
  for (int i = 0; i < stack_count; ++i)
    if (supplies[i].size > max_height)
      max_height = supplies[i].size;

  for (int y = max_height - 1; y >= 0; --y) {
    for (int x = 0; x < stack_count; ++x) {
      struct stack *s = &supplies[x];

      if (y < s->size)
        printf("[%c] ", s->crates[y]);
      else
        printf("    ");
    }
    printf("\n");
  }
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  // Read the initial data
  int stack_count = read_stack_count(file);
  char *rows[stack_count];
  int row_count = read_rows(file, rows, stack_count);

  // Initialize an array of empty stacks
  struct stack *supplies = malloc(sizeof(struct stack) * stack_count);
  for (int i = 0; i < stack_count; ++i)
    stack_init(&supplies[i], MAX_CRATES);

  // Append crates to corresponding stacks, bottom to top
  for (int i = row_count - 1; i >= 0; --i) {
    char *row = rows[i];

    for (int j = 0; j < stack_count; ++j)
      if (row[j] != ' ')
        stack_append(&supplies[j], row[j]);

    free(row);
  }

  // Skip the number line
  fseek(file, stack_count * 4 - 1, SEEK_CUR);

  // Read and execute the instructions
  int count, from, to;
  while (fscanf(file, "move %d from %d to %d\n", &count, &from, &to) != EOF) {
    struct stack *s1 = &supplies[from - 1];
    int index = s1->size - count;

    for (int i = 0; i < count; ++i) {
      char crate = stack_remove(s1, index);
      stack_append(&supplies[to - 1], crate);
    }
  }

  print_supplies(supplies, stack_count);

  char top[stack_count + 1];

  for (int i = 0; i < stack_count; ++i) {
    struct stack s = supplies[i];
    top[i] = s.crates[s.size - 1];
    top[i + 1] = '\0';
    stack_clear(&s);
  }

  printf("Top crates: %s\n", top);

  free(supplies);
  fclose(file);
}
