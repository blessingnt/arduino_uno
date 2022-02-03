
// PUT YOUR INCLUDES FOR TABS HERE
#include "bowser.h"
#include "fish.h"
#include "cloud.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

int neoPin = 6;
// MODIFY TO MATCH YOUR MATRIX DIMENSIONS
int cols = 32;
int rows = 8;

Adafruit_NeoMatrix neo(cols, rows, neoPin,
                       NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                       NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                       NEO_GRB            + NEO_KHZ800);

// Probably do not need to modify these variables.
int x = 0;
int y = 0;
int img = 0;
int diff = -1;
int minBound = 0;

// MODIFY THIS FOR THE NUM OF TABS YOU HAVE
int numImages = 3;

// MODIFY TO MATCH YOUR ARDUINO MODEL
// If using UNO or UNO WIFI, place button on pin 2 or 3.
// If using MKR, place button on pin 4, 5, or 6.
int buttonPin = 1;

void setup()
{
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  // Sets up interrupt on buttonPin
  attachInterrupt(digitalPinToInterrupt(buttonPin), nextImage, CHANGE);

  neo.begin();
  neo.setBrightness(5);
  neo.fillScreen(neo.Color(255, 0, 0));
  neo.show();

  Serial.println("READY");
}

/**
   Draws the sprites.
   DO NOT MODIFY THIS FUNCTION
*/
void loop()
{
  neo.clear();
  drawImage();
  neo.show();
  delay(200);

  // Controls the sprite image bounce effect.
  y = y + diff;
  if (y < minBound)
  {
    diff = 1;
  }
  if (y > 0)
  {
    diff = -1;
  }
}

/**
   Handles transitions between images on button interrupt.
   DO NOT MODIFY THIS FUNCTION
*/
void nextImage()
{
  if (digitalRead(buttonPin) == HIGH)
  {
    Serial.println("NEXT IMAGE ");

    img = img + 1;
    img = img % numImages;

    x = 0;
    y = 0;
    diff = -1;
  }
}

/**
 * Controls how the current image is draw on the matrix.
 * Modify this function to include logic for each sprite.
 */
void drawImage()
{
  //draw bowser (32x32)
if (img == 0)
{
  minBound = -24;
  neo.drawRGBBitmap(x, y, (const uint16_t*) bowser, 32, 32);
}
else if (img == 1)
{
  minBound = -8;
  neo.drawRGBBitmap(x, y, (const uint16_t*) fish, 16, 16);
}
else if (img == 2)
{
  minBound = -8;
  neo.drawRGBBitmap(x, y, (const uint16_t*) cloud, 16, 16);
}
}
