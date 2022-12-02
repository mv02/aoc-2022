#include <stdio.h>

enum choice {ROCK, PAPER, SCISSORS};
enum result {LOSS, DRAW, WIN};

/*
 * Decides which option to choose to end the round with given result.
 * @param opponent The opponent's choice
 * @param result The desired round result
 * @return The correct option
 */
enum choice decide(enum choice opponent, enum result result)
{
  if (result == DRAW)
    return opponent;
  if (opponent == ROCK)
    return result == WIN ? PAPER : SCISSORS;
  if (opponent == PAPER)
    return result == WIN ? SCISSORS : ROCK;
  return result == WIN ? ROCK : PAPER;
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  int score = 0;
  char input1, input2;
  enum choice player, opponent;
  enum result result;

  while (fscanf(file, "%c %c\n", &input1, &input2) != EOF) {
    // Convert ABC/XYZ to 012
    opponent = input1 - 65;
    result = input2 - 88;

    player = decide(opponent, result);

    score += player + 1;

    if (result == WIN)
      score += 6;
    else if (result == DRAW)
      score += 3;
  }

  printf("Score: %d\n", score);
  fclose(file);
}
