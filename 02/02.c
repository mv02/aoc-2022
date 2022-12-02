#include <stdio.h>

enum choice {ROCK, PAPER, SCISSORS};

/*
 * Determines which player has won the round.
 * @return 1 if player 1 wins, 2 if player 2 wins, 0 if draw
 */
int get_winner(enum choice p1, enum choice p2)
{
  if (p1 == p2)
    return 0;
  if (p1 == ROCK && p2 == SCISSORS)
    return 1;
  if (p1 == PAPER && p2 == ROCK)
    return 1;
  if (p1 == SCISSORS && p2 == PAPER)
    return 1;
  return 2;
}

int main()
{
  FILE *file = fopen("input.txt", "r");

  int score = 0, winner;
  char input1, input2;
  enum choice player, opponent;

  while (fscanf(file, "%c %c\n", &input1, &input2) != EOF) {
    // Convert ABC/XYZ to 012
    opponent = input1 - 65;
    player = input2 - 88;

    score += player + 1;
    winner = get_winner(player, opponent);

    if (winner == 1)
      score += 6;
    else if (winner == 0)
      score += 3;
  }

  printf("Score: %d\n", score);
  fclose(file);
}
