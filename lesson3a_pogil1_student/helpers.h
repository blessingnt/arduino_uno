#include "board.h"

extern Board board;

int getStreakLength(int i)
{
  int count = 1;

  while (i < 7)
  {
    if (board.getColor(i) != GRAY && board.getShape(i) == board.getShape(i + 1))
    {
      count = count + 1;
    }
    else
    {
      return count;
    }
    i = i + 1;
  }

  return count;
}

void putColorBetween(int first, int until, uint16_t color)
{
  int i = first;
  while (i < until)
  {
    board.putColor(i, color);
    i = i + 1;
  }
}

void clearStreak(int first, int until)
{
  putColorBetween(first, until, GRAY);
  board.show();
  delay(100);

  putColorBetween(first, until, BLACK);
  board.show();
  delay(100);

  putColorBetween(first, until, GRAY);
  board.show();
  delay(100);

  putColorBetween(first, until, BLACK);
  board.show();
  delay(100);

  putColorBetween(first, until, GRAY);
  board.show();
  delay(100);

  putColorBetween(first, until, BLACK);
  board.show();
  delay(100);

  putColorBetween(first, until, GRAY);
  board.show();
}


int pickRandomShape()
{
  return random(0, 6);
}

uint16_t pickRandomColor()
{
  int i = random(0, 4);
  //Serial.println("color = " + String(i));

  if (i == 0)
  {
    return RED;
  }
  if (i == 1)
  {
    return GREEN;
  }
  if (i == 2)
  {
    return BLUE;
  }

  return YELLOW;
}
