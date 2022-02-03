#include <Adafruit_NeoPixel.h>

int numLEDs = 256;
int neoPin = 6;
int i = 0;
bool shouldTurnOff = false;


Adafruit_NeoPixel neo(numLEDs, neoPin);

void setup()
{
  Serial.begin(9600);
  neo.begin();
  neo.setBrightness(10);
  neo.clear();
}

void loop()
{
  int col = i / 8;
  Serial.println("col = " + String(col));

  Serial.println("i = " + String(i));
  uint32_t px = neo.Color(255, 0, 0);
  if (col == 0)
  {
    // RED
    px = neo.Color(255, 0, 0);
  }
  if (col % 1 == 0)
  {
    // ORANGE
    px = neo.Color(255, 128, 0);
  }
  if (col % 2 == 0)
  {
    // YELLOW
    px = neo.Color(255, 247, 0);
  }
  if (col % 3 == 0)
  {
    // GREEN
    px = neo.Color(0, 255, 0);
  }
  if (col % 4 == 0)
  {
    // BLUE
    px = neo.Color(0, 0, 255);
  }
  if (col % 5 == 0)
  {
    // PURPLE
    px = neo.Color(115, 0, 255);
  }
  if (col % 6 == 0)
  {
    // RED
    px = neo.Color(255, 0, 0);
  }
  // Repeat this pattern for every if statement.
  // Change the highlighted number to match the color.

  if (shouldTurnOff == true)
  {
    neo.setPixelColor(i, 0);
  }
  else
  {
    neo.setPixelColor(i, px);
  }
  neo.show();
  delay(100);
  i = i + 1;

  if (i == 256)
  {
    i = 0;
    shouldTurnOff = !shouldTurnOff; // flip bool to opposite
  }
}
