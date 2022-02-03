#include "board.h"
#include "helpers.h"

int joyXPin = A0;
int joyBtnPin = 1;

int neoPin = 6;
int width = 32;
int height = 8;
Board board(neoPin, width, height);

void setup()
{
  Serial.begin(9600);
  pinMode(joyBtnPin, INPUT_PULLUP);
  board.begin();
  randomSeed(analogRead(A2));
  assignRandom(0, 8);

}

void loop()
{
int joyX = analogRead(joyXPin);
Serial.println(joyX);

if (joyX > 600)
{
  board.moveRight();
}
if (joyX < 500)
{
  board.moveLeft();
}

if (digitalRead(joyBtnPin) == LOW)
{
  int i = board.getArrowIndex();
  shuffle(i, i + 1);
  assignRandom(i, i + 1);
}

if (digitalRead(joyBtnPin) == HIGH)
{
  int i = board.getArrowIndex();
  shuffle(i, i + 1);
  findStreaks();
}

  board.show();
  delay(100);
}

void assignRandom(int first, int until)
{
  int i = first;
  while (i < until)
  {
    board.putShape(i, pickRandomShape());
    board.putColor(i, pickRandomColor());
    i = i + 1;
  }
}

void shuffle(int first, int until)
{
  int shuffles = 0;
  while (shuffles < 10)
  {
    assignRandom(first, until);
    board.show();
    delay(100);
    shuffles++;
  }
}


void findStreaks()
{
  int i = 0;
  while (i < 7)
  {
    int count = getStreakLength(i);
    if (count > 1)
{
  clearStreak(i, i + count);
  i = i + count - 1;
}
    i = i + 1;
  }
}

