#ifndef BOARD_H
#define BOARD_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

enum Shapes {
  SQUARE,
  SQUARE_EMPTY,
  CIRCLE,
  CROSS,
  TRIANGLE,
  EX,
};

uint16_t RED = Adafruit_NeoMatrix::Color(255, 0, 0);
uint16_t GREEN = Adafruit_NeoMatrix::Color(0, 255, 0);
uint16_t BLUE = Adafruit_NeoMatrix::Color(0, 0, 255);
uint16_t YELLOW = Adafruit_NeoMatrix::Color(255, 255, 0);
uint16_t GRAY = Adafruit_NeoMatrix::Color(100, 100, 100);
uint16_t BLACK = 0;

class Board
{
  private:
    Adafruit_NeoMatrix *neo;
    int shapes[8];
    uint16_t colors[8];
    int arrow_index = 0;
    int w;
    int numShapes;

    void drawArrow();

  public:
    Board(uint16_t pin, int width, int height);
    void begin();
    void show();
    
    int getArrowIndex() {
      return arrow_index;
    }
    void moveRight() {
      if (arrow_index < numShapes - 1)
      {
        arrow_index++;
      }
    }
    void moveLeft()
    {
      if (arrow_index > 0)
      {
        arrow_index--;
      }
    }
    int getShape(int i) {
      return shapes[i];
    }
    void putShape(int i, int s) {
      shapes[i] = s;
    }
    uint16_t getColor(int i) {
      return colors[i];
    }
    void putColor(int i, uint16_t c)
    {
      colors[i] = c;
    }
};

Board::Board(uint16_t pin, int width, int height)
{
  neo = new Adafruit_NeoMatrix(width, height, pin,
                               NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                               NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                               NEO_GRB            + NEO_KHZ800);
  w = width;
  numShapes = (width / 4);
}

void Board::begin()
{
  neo->begin();
  neo->setTextWrap(false);
  neo->setBrightness(10);
  neo->fillScreen(0);
}

void Board::show()
{
  neo->fillScreen(0);

  int i = 0;

  while (i < 8)
  {
    int x = 1 + 4 * i;
    int y = 1;

    if (shapes[i] == SQUARE)
      neo->fillRect(x, 1, 3, 3, colors[i]);
    if (shapes[i] == SQUARE_EMPTY)
      neo->drawRect(x, 1, 3, 3, colors[i]);
    if (shapes[i] == CIRCLE)
      neo->fillCircle(x + 1, 2, 1, colors[i]);
    if (shapes[i] == CROSS)
      neo->drawCircle(x + 1, 2, 1 , colors[i]);
    if (shapes[i] == TRIANGLE)
      neo->fillTriangle(x + 1, 1, x, 3, x + 2, 3, colors[i]);
    if (shapes[i] == EX)
    {
      neo->drawLine(x, 1, x + 2, 3, colors[i]);
      neo->drawLine(x + 2, 1, x, 3, colors[i]);
    }

    i = i + 1;
  }

  drawArrow();

  neo->show();
}

void Board::drawArrow() {
  int x = 2 + arrow_index * 4;
  int y = 4;
  
  neo->drawLine(x, y, x, y + 3, neo->Color(255, 255, 255));
  neo->drawPixel(x - 1, y + 1, neo->Color(255, 255, 255));
  neo->drawPixel(x + 1, y + 1, neo->Color(255, 255, 255));
}

#endif
